/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:29:21 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/30 09:29:21 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# include "../libs/libft/includes/libft.h"
# include "../libs/libft/includes/ft_printf.h"

# define ORANGE "\033[38;2;255;165;0m"
# define PURPLE "\033[38;2;180;100;255m"
# define CYAN "\033[38;2;0;200;200m"
# define BOLD "\033[1m"
# define RESET "\033[0m"
# define COLOR_CHANGE_INTERVAL 100

void	signal_handler(int sig, siginfo_t *info, void *context);
void	send_signal(int pid, char c);
void	ack_handler(int sig);

#endif
