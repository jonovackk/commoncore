/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:39:57 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/31 13:50:44 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

//Standard C libraries

# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

//Protoypes

void			ft_putchar_count(int c, int *count);
void			ft_putstr_count(char *str, int *count);
void			ft_putptr_count(void *ptr, int *count);
void			ft_putnbr_count(int nbr, int *count);
void			ft_putnbr_unsigned_count(unsigned int nbr, int *count);
void			ft_put_hex_count(unsigned long ptr, const char *hex_digits, int *count);

#endif //FT_PRINTF_H
