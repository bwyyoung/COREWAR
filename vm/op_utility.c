/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:12:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/14 17:37:19 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		inc_pc(uint32_t *regs, int inc)
{
	regs[0] = (regs[0] + inc) % MEM_SIZE;
}

void		modify_carry(t_process *process, uint32_t val)
{
	process->carry = (val) ? 0 : 1;
}

int			get_idx_val(int val)
{
	if (val >= MEM_SIZE)
		val -= 0x10000;	
	return (val % IDX_MOD);
}
