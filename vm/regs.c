/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:36:41 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/13 18:17:35 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			valid_reg_num(uint8_t reg_num)
{
	return (reg_num > 0 && reg_num < REG_NUMBER);
}

int			is_reg_num_invalid(uint8_t reg_num)
{
	return (reg_num == 0 || reg_num >= REG_NUMBER);
}

int			get_reg_val(t_process *process, uint8_t reg_num)
{
	return (process->regs[reg_num]);
}

void		set_reg_val(t_process *process, uint8_t reg_num, int new_val)
{
	if (is_reg_num_invalid(reg_num))
		return ;
	process->regs[reg_num] = new_val;
}
