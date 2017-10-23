/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/23 12:06:57 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** If the carry == 1 zjmp will increase the pc of the process by the idx_val of its
** only param
** else it will do nothing but inc its pc to skip the jmp instruction and its parameter.
*/

void	op_zjmp(t_env *env, t_process *process)
{
	(void)env;
	//ft_printf("op_zjmp |%i | %i|  ---------!!!!! \n", process->process_num, process->carry);

	//ft_printf("-----------------\n");
	if (process->carry == 1)
		inc_pc(process->regs, get_idx_val(process->params[0].val));
	else
		inc_pc(process->regs, 1 + IND_SIZE);
}

/*
// 42
zjmp: there’s never been, isn’t and will never be an
argument’s coding byte behind
this operation where the opcode is 9.
It will take an index and jump to this address
if the carry is 1.

// epitech
This instruction is not followed by any parameter encoding byte.
It always takes an index (IND_SIZE) and makes a jump at this
index if the carry is set to 1. If the carry is null, zjmp
does nothing but consumes the same amount of time.
zjmp %23 does : If carry == 1, store (PC + (23 % IDX_MOD)) in the PC.
*/
