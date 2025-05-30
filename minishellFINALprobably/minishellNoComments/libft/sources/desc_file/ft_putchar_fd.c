/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:37:29 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 15:09:56 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Writes the character c to the given file descriptor fd.
 * Useful for outputting characters to files or specific outputs
 * like standard output (1) or standard error (2).
 */

 void	ft_putchar_fd(char c, int fd)
 {
	 write(fd, &c, 1);
 }
