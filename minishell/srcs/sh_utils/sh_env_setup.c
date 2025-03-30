#include "../../includes/minishell.h"

/**
 * @brief Retrieves or updates the global environment context.
 * 
 * Stores a static pointer to the shell environment, updating it if a new
 * pointer is provided.
 * 
 * @param env Pointer to the environment list (optional for updates).
 * @return The current environment context.
 */
t_sh_env *sh_env_context(t_sh_env **env)
{
    static t_sh_env *env_ctx;

    // If the environment context doesn't exist or env is provided, update it
    if (!env_ctx || env)
        env_ctx = *env; // Possible error: ensure *env is valid and not NULL.
    return (env_ctx); // Returns the current environment context
}

/**
 * @brief Sets default environment variables if they are missing.
 * 
 * 1. Unsets OLDPWD.
 * 2. Sets PWD to the current directory.
 * 3. Sets _ to the shell executable path.
 * 
 * @param env Pointer to the environment list.
 * @param argv Program arguments (used for executable path).
 */
void sh_env_defaults(t_sh_env **env, char **argv)
{
    char *tmp;

    // Unset OLDPWD environment variable
    sh_update_env(env, "OLDPWD", NULL);

    // Set PWD to the current working directory
    tmp = sh_get_pwd();
    if (tmp)
        sh_update_env(env, "PWD", tmp); // Possible error: ensure `sh_get_pwd()` doesn't return NULL.

    // Set _ to the executable path (argv[0])
    // FIXED ERROR: Removed stray 'm' in str_join
    tmp = str_join(sh_get_pwd(), argv[0], "/", 0b01);
    if (tmp)
        sh_update_env(env, "_", tmp); // Possible error: Ensure the result of str_join is valid.
}

/**
 * @brief Initializes the shell environment from envp or sets defaults.
 * 
 * 1. Copies envp into the shell's environment list.
 * 2. Sets defaults if envp is empty.
 * 3. Increments SHLVL (shell level).
 * 4. Sets SHELL and LOGOPWD variables.
 * 
 * @param argv Program arguments.
 * @param envp Environment variables from main.
 * @return Pointer to the initialized environment list.
 */
t_sh_env *sh_env_init(char **argv, char **envp)
{
    t_sh_env *env;
    char *tmp;
    int i;

    i = -1;
    env = NULL;
    tmp = NULL;

    // Loop through envp and add each environment variable to env list
    while (envp[++i])
        sh_append_env(&env, sh_create_env_var(envp[i]));

    // If envp is empty, set defaults
    if (i == 0)
        sh_env_defaults(&env, argv);

    // Update SHLVL: increment if exists, else set to "1"
    if (sh_find_env(env, "SHLVL") && sh_find_env(env, "SHLVL")->values)
        tmp = ft_itoa(1 + ft_atoi(sh_find_env(env, "SHLVL")->values[0]));
    else
        tmp = ft_strdup("1");

    if (tmp)
        sh_update_env(&env, "SHLVL", tmp); // Possible error: check if tmp is valid before updating.

    // Set SHELL variable if envp is not empty
    if (i)
    {
        tmp = ft_strdup("minishell");
        if (tmp)
            sh_update_env(&env, "SHELL", tmp); // Possible error: ensure strdup succeeded.
    }

    // Set LOGOPWD variable to include "/logo" in PWD path
    if (sh_find_env(env, "PWD") && sh_find_env(env, "PWD")->values)
    {
        tmp = str_join(sh_find_env(env, "PWD")->values[0], "/logo", 0b00);
        if (tmp)
            sh_update_env(&env, "LOGOPWD", tmp); // Possible error: ensure str_join didn't return NULL.
    }

    return (env); // Return the initialized environment list
}