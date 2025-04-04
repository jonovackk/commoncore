#include "../../includes/minishell.h"

t_sh_exec   *sh_exec_init(void)
{
    t_sh_exec   *exec_ctx;

    exec_ctx = malloc(sizeof(t_sh_exec));
    if (!exec_ctx)
        return (NULL);
    exec_ctx->running_procs = NULL;
    exec_ctx->active_pipes = NULL;
    return (exec_ctx);
}