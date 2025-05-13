/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:50:11 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/05 11:46:28 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_printf(char const *str, ...);
void	ft_print_char(char c, int *i);
void	ft_print_num(int num, int *i);
void	ft_print_ptr(void *ptr, int *i);
void	ft_print_str(char *str, int *i);
void	ft_print_num_unsigned(unsigned int num, int *i);
void	ft_print_hex(unsigned int num, int *i, char *base);
void	ft_print_num_base(unsigned long int p, char *base, int *i);
int     ft_format(int fd, va_list args, char c);
int     ft_printer(int fd, const char *format, va_list args);
int     ft_dprintf(int fd, const char *format, ...);






#endif
