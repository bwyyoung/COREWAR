/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/16 12:37:08 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
zjmp: there’s never been, isn’t and will never be an
argument’s coding byte behind
this operation where the opcode is 9.
It will take an index and jump to this address
if the carry is 1.

This instruction is not followed by any parameter encoding byte.
It always takes an index (IND_SIZE) and makes a jump at this
index if the carry is set to 1. If the carry is null, zjmp
does nothing but consumes the same amount of time.
zjmp %23 does : If carry == 1, store (PC + (23 % IDX_MOD)) in the PC.
*/

void	op_zjmp(t_env *env, t_process *process, uint32_t pc)
{
	int index;

	index = get_board_val(env->board, pc + 1, IND_SIZE);
	if (process->carry == 1)
		inc_pc(process->regs, get_idx_val(index));
	else
		inc_pc(process->regs, 1 + IND_SIZE);
}
