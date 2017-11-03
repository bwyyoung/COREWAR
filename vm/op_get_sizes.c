/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_get_sizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:16:05 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 19:03:16 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Return the number of bytes the param is using on the board.
** So a register is represented by one byte on the board 0x01 == reg1
** Note: a direct value is sometimes 4 bytes big and sometimes when
** representing an index it's 2 bytes big;
*/

int		get_param_size(uint8_t type, int label_size)
{
	int size;

	size = 0;
	if (type == REG_CODE)
		size = 1;
	else if (type == DIR_CODE)
		size = label_size;
	else if (type == IND_CODE)
		size = IND_SIZE;
	return (size);
}

/*
** Returns the size of ops that don't have a type byte.
*/

int		get_op_size_no_type(uint8_t op)
{
	int size;

	size = 1;
	if (op == live)
		size += DIR_SIZE;
	else if (op == aff)
		size += IND_SIZE + 1;
	else
		size += IND_SIZE;
	return (size);
}

/*
** Returns the full size of a op on the board
** Example:
**		in .s:			zjmp %15
**		on board:		09 00 0f
**		returns size	3
*/

int		get_op_size(t_env *env, t_process *process)
{
	int size;
	int op;
	int num_params;

	op = process->op;
	if (!env->op_tab[op].has_type)
		return (get_op_size_no_type(op));
	size = 2;
	num_params = env->op_tab[op].num_params;
	while (num_params--)
		size += get_param_size(process->param_type[num_params],
								env->op_tab[op].label_size);
	return (size);
}
