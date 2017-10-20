/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:12:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 11:08:36 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Change the pc value of a process. (regs[0] == pc)
** Use % MEM_SIZE because memory is circular
** MEM_SIZE == 4096 == 4 * 1024
*/
void		inc_pc(uint32_t *regs, int inc)
{
	regs[0] = (regs[0] + inc) % MEM_SIZE;
}

/*
** Modify the carry of a process
*/
void		modify_carry(t_process *process, uint32_t val)
{
	process->carry = !val;
}

/*
** If the val is more than MEM_SIZE it means that the val is behind the pc,
** so the val needs to be negative which is done by taking the val minus 0x10000.
** Example:
** if zjmp has the param 0xfffb (like in zork)
** we will take 0xfffb - 0x10000 which is -5
** then return -5 % IDX_MOD (IDX_MOD == 512 == MEM_SIZE / 8)
** which means we will return -5
*/
int			get_idx_val(int val)
{
	if (val >= MEM_SIZE)
		val -= 0x10000;
	return (val % IDX_MOD);
}
