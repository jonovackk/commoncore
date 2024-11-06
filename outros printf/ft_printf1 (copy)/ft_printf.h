/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:46:44 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:46:51 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// Protótipo da função principal ft_printf
int		ft_printf(const char *format, ...);

// Funções de conversão para cada tipo de formato
int		ft_print_char(char c);
int		ft_print_hex_lower(unsigned int num);
int		ft_print_hex_upper(unsigned int num);
int		ft_print_int(int n);
int		ft_print_percent(void);
int		ft_print_pointer(void *ptr);
int		ft_print_string(char *str);
int		ft_print_unsigned(unsigned int n);

// Função auxiliar para impressão de números inteiros
void	ft_putnbr_fd(int n, int fd);

#endif /* FT_PRINTF_H */
/*#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// Protótipo da função principal ft_printf
int		ft_printf(const char *format, ...);

// Funções de conversão para cada tipo de formato
int		ft_print_char(char c);
int		ft_print_hex_lower(unsigned int num);
int		ft_print_hex_upper(unsigned int num);
int		ft_print_int(int n);
int		ft_print_percent(void);
int		ft_print_pointer(void *ptr);
int		ft_print_string(char *str);
int		ft_print_unsigned(unsigned int n);

// Função auxiliar para impressão de números inteiros
void	ft_putnbr_fd(int n, int fd);

#endif*/
