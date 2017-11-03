/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:36:41 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/02 10:16:38 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		valid_reg_num(int reg_num)
{
	return (reg_num > 0 && reg_num <= REG_NUMBER);
}

int		is_reg_num_invalid(int reg_num)
{
	return (reg_num == 0 || reg_num > REG_NUMBER);
}

int		get_reg_val(t_process *process, int reg_num)
{
	return (process->regs[reg_num]);
}

void	set_reg_val(t_process *process, int reg_num, int new_val)
{
	process->regs[reg_num] = new_val;
}
