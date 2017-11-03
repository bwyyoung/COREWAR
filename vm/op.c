/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/11/03 14:31:58 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** t_op contains info about each of the ops.
**
** {name, num_params, param_types, cycles, has_type, label_size, use_idx}
**
** name			(name of the op)
** num_params	(number of params)
** param_types	(what kind of types are valid as params)
** cycles		(how many cycles the op uses)
** has_type		(if the op has a type byte)
** label_size	(if the direct value is of size 2 or 4)
** use_idx		(if the op uses IDX_MOD)
*/

t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 10, 0, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 4, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 4, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 4, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 4, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		6, 1, 4, 1},
	{"zjmp", 1, {T_DIR}, 20, 0, 2, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 2, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 2, 1},
	{"fork", 1, {T_DIR}, 800, 0, 2, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 4, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 2, 1},
	{"lfork", 1, {T_DIR}, 1000, 0, 2, 0},
	{"aff", 1, {T_REG}, 2, 1, 4, 0},
};

t_op		*get_op_tab(void)
{
	return (g_op_tab);
}
