/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:58:36 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/04 15:02:47 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

int				ft_putchar(int c);
int				ft_putnbr(int n);
int				ft_putstr(char *s);
int				ft_printf(const char *str, ...);
unsigned int	ft_num_nosign(unsigned int num);
int				ft_punt_hexa(void *p);
int				ft_strlen(char *s);
int				ft_hexa_min(int num);
int				ft_hexa_mayus(int num);

#endif
