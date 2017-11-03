/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:12:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 17:48:39 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Change the pc value of a process. (regs[0] == pc)
** Use % MEM_SIZE because memory is circular
** MEM_SIZE == 4096 == 4 * 1024
*/

void		inc_pc(t_process *process, int inc)
{
	process->regs[0] = get_board_pos(process->regs[0] + inc);
}

/*
** Modify the carry of a process
*/

void		modify_carry(t_process *process, int val)
{
	process->carry = !val;
}

/*
** Convert value to int16_t and then mod it with IDX_MOD
*/

// int16_t		get_idx_val(int16_t val)
// {
// 	return (val % IDX_MOD);
// }

int			get_board_pos(int val)
{
	return ((0 > (val %= MEM_SIZE)) ? val + MEM_SIZE : val);
}
