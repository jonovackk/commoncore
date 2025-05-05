/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:01:09 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 10:09:05 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> //For size_t
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE	1024

# define HEX_LOWCASE "0123456789abcdef"
# define HEX_UPCASE "0123456789ABCDEF"

//# ------------------------------------
//# Functions to Manipulate Characters #
//# ------------------------------------

int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_putchar(char c);
int		ft_putnbr(int nb);
int		ft_isspace(int c);


//# ------------------------------------
//# Functions to Manipulate Strings ####
//# ------------------------------------

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_putstr(char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little,
			size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2, char *c, int tofree);
char	*ft_strsjoin(char **strs, char *sep, int tofree);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_putptr(unsigned long int ptr);
int		ft_puthex(unsigned int number, int flag);
char	*ft_strndup(char *str, int n);
char	*ft_strdup(char *str);
int		ft_tab_len(char **tab);
void	ft_swap_strs(char **a, char **b);
void	ft_sort_strs_tab(char **tab, int size);
void	ft_sort_lowstrs_tab(char **tab, int size);
int		ft_strcspn(char *s, char *rejects);
char	*ft_strtok(char *str, char *token);


//# ------------------------------------
//# Functions to Manipulate Memory #####
//# ------------------------------------

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_free_tab(void **tab);
void	ft_free_big_tab(void **tab, int depth);


//# --------------------------------------------------
//# Functions to Conversion/Strings for Integers #####
//# --------------------------------------------------

char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);

//# ------------------------------------
//# Functions File Descriptor      #####
//# ------------------------------------

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//# ------------------------------------
//# Get Next Line                  #####
//# ------------------------------------

char	*get_next_line(int fd);

//# ------------------------------------
//# FT PRINTF                      #####
//# ------------------------------------

int		ft_printf(const char *str, ...);
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
