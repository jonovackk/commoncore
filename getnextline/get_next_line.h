/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:26:53 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/14 16:42:15 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fnctl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	strlen_at(const char *s, int c);
char	*cpy_buffer(const char *s, size_t n);
char	*find_chr(const char *s, int c);
char	*merge_previous_and_current(char *s1, char const *s2);

#endif

