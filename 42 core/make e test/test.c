/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:15:50 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/06 10:46:15 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int main() {
    // Testando %c
    char c = 'A';
    ft_printf("Teste de %%c: ");
    ft_printf("%c\n", c);

    // Testando %s
    char *str = "Hello, World!";
    ft_printf("Teste de %%s: ");
    ft_printf("%s\n", str);

    // Testando %p
    void *ptr = (void *)0x7fffd9b8c5f0;
    ft_printf("Teste de %%p: ");
    ft_printf("%p\n", ptr);

    // Testando %d e %i
    int num = 42;
    ft_printf("Teste de %%d e %%i: ");
    ft_printf("%d %i\n", num, num);

    // Testando %u
    unsigned int u_num = 42;
    ft_printf("Teste de %%u: ");
    ft_printf("%u\n", u_num);

    // Testando %x
    ft_printf("Teste de %%x: ");
    ft_printf("%x\n", num);

    // Testando %X
    ft_printf("Teste de %%X: ");
    ft_printf("%X\n", num);

    // Testando %%
    ft_printf("Teste de %%: ");
    ft_printf("%%\n");

    return 0;
}


