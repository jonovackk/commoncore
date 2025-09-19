/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:47:20 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 14:16:10 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include <limits.h>
# include <stdio.h> // Apenas para ft_printf
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}					t_stack;

// main.c
int					main(int argc, char **argv);

// sort_radix.c
void				radix_sort(t_stack **stack_a, t_stack **stack_b);

// stack_bits.c
int					get_max_bits(t_stack *stack);
int					stack_size(t_stack *stack);

// stack_nodes.c
t_stack				*new_node(int value);
void				add_node(t_stack **stack, t_stack *new);
void				free_stack(t_stack *stack);

// stack_init.c
t_stack				*init_stack(char **argv);
int					is_sorted(t_stack *stack);

// op_push.c
void				push_a(t_stack **a, t_stack **b);
void				push_b(t_stack **a, t_stack **b);

// op_rotate.c
void				rotate_a(t_stack **a);
void				rotate_b(t_stack **b);

// op_revrotate.c
void				rev_rotate_a(t_stack **a);
void				rev_rotate_b(t_stack **b);

// op_swap.c
void				swap_a(t_stack **a);
void				swap_b(t_stack **b);

// val_utils.c
int					validate_input(char **argv);
int					is_number(char *str);

// general_utils.c
long				ft_atoi(const char *str);
int					ft_free_all(char **str);
int					check_duplicates(char **argv);
void				print_stack(t_stack *stack);

// normalize_stack.c
void				normalize_values(t_stack *stack);

// sort_small.c
void				sort_three(t_stack **a);
void				sort_five(t_stack **a, t_stack **b);
int					get_smallest(t_stack *stack);
int					get_second_smallest(t_stack *stack);

// sort_stack.c
void				sort_stack(t_stack **stack_a, t_stack **stack_b);
int					get_position(t_stack *stack, int value);

#endif
