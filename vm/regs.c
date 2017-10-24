/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:36:41 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 11:25:44 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			valid_reg_num(uint32_t reg_num)
{
	return (reg_num > 0 && reg_num < REG_NUMBER);
}

int			is_reg_num_invalid(uint32_t reg_num)
{
	return (reg_num == 0 || reg_num >= REG_NUMBER);
}

uint32_t	get_reg_val(t_process *process, uint32_t reg_num)
{
	//ft_printf("get_reg_val %i\n", reg_num);
	return (process->regs[reg_num]);
}

void		set_reg_val(t_process *process, uint32_t reg_num, uint32_t new_val)
{
	if (is_reg_num_invalid(reg_num))
		return ;
	process->regs[reg_num] = new_val;
}
