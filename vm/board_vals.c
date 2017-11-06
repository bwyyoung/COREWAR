/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:01:59 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/05 14:28:53 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Get a value from the board and reverse its endian.
** Example:
**		The number ff fb is stored as ff fb in C but
**		on the board it is stored as fb ff.
*/

int			get_board_val(uint8_t *board, int index, int size)
{
	uint8_t		*pval;
	int			val;
	int			i;

	while (index < 0)
		index += MEM_SIZE;
	val = 0;
	i = 0;
	pval = (uint8_t*)&val;
	while (size--)
		pval[i++] = board[(index + size) % MEM_SIZE];
	return (val);
}

/*
** Set a value on the board. Though before writing it we
** have to reverse its endian.
*/

void		set_board_val(t_env *env, t_process *process, int index, int val)
{
	uint8_t		*pval;
	int			size;

	while (index < 0)
		index += MEM_SIZE;
	size = REG_SIZE;
	pval = (uint8_t*)&val;
	while (size--)
	{
		env->board[index % MEM_SIZE] = pval[size];
		env->prog_num_board[index % MEM_SIZE] = process->prog_num;
		index++;
	}
}
