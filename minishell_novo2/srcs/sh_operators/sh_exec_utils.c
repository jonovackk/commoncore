#include "../../includes/minishell.h"

/**
 * @brief Creates a child process with a specific exit code
 * 
 * Forks a child process and sets up cleanup before exiting
 * 
 * @param err_code Exit code for the child process
 * @param executor Execution context to be cleaned up
 */
void sh_create_fake_pid_child(int err_code, t_sh_exec *executor)
{
    pid_t child;

    child = fork();
    if (child == -1)
        return;

    if (child == 0)
    {
        // close and clean up resources
        sh_tree_fd_cleanup(sh_command_tree_state(0, NULL));
        sh_fork_cleanup(executor);
        exit(err_code);
    }

    // add child PID to process list
    sh_pid_push(&(executor->running_procs), sh_init_pid(child));
}

/**
 * @brief Processes input and output redirections for a command
 * 
 * Duplicates file descriptors for input and output
 * 
 * @param cmd Command with redirection information
 * @param node_fd Original node file descriptors
 */
void sh_process_redirections(t_sh_cmd *cmd, int *node_fd)
{
    int file_descriptors[2];

    // initialize fd
    file_descriptors[0] = node_fd[0];
    file_descriptors[1] = node_fd[1];

    // override input fd if specified
    if (cmd->input_fd != STDIN_FILENO)
        file_descriptors[0] = cmd->input_fd;

    // override output fd if specified
    if (cmd->output_fd != STDOUT_FILENO)
        file_descriptors[1] = cmd->output_fd;

    // redirect input if needed
    if (file_descriptors[0] != STDIN_FILENO)
        dup2(file_descriptors[0], STDIN_FILENO);

    // redirect output if needed
    if (file_descriptors[1] != STDOUT_FILENO)
        dup2(file_descriptors[1], STDOUT_FILENO);

    // close command-related fd
    sh_cmd_cleanup(cmd);
}

/**
 * @brief Handles command exit status and signals
 * 
 * Processes core dump and termination signals
 * Updates global exit status accordingly
 * 
 * @param exit_status Exit status of the process
 */
void sh_process_command_exit(int exit_status)
{
    // check for core dump
    if (!WIFEXITED(exit_status) && WCOREDUMP(exit_status))
    {
        ft_dprintf(2, "Quit (core dumped)\n");
        g_shell_exit_status = 131;
    }

    // check for specific termination signals
    if (WTERMSIG(exit_status) == SIGINT)
    {
        ft_dprintf(2, "\n");
        g_shell_exit_status = 130;
    }
}

/**
 * @brief Performs cleanup during fork exit
 * 
 * Closes resources, clears history and environment
 * 
 * @param executor Execution context to be cleaned up
 */
void sh_fork_cleanup(t_sh_exec *executor)
{
    // close executor resources
    sh_exec_release(executor);
    free(executor);

    // clear readline history
    rl_clear_history();

    // clear environment and execution tree
    sh_destroy_env_list(sh_env_context(NULL));
    sh_destroy_tree(sh_command_tree_state(0, NULL));
}