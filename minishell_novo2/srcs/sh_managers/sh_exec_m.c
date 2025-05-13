/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:09 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:07:10 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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