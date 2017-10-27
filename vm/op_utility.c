/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:12:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/27 13:58:22 by dengstra         ###   ########.fr       */
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
	process->regs[0] = (process->regs[0] + inc) % MEM_SIZE;
}

/*
** Modify the carry of a process
*/
void		modify_carry(t_process *process, uint32_t val)
{
	process->carry = !val;
}

/*
** Convert value to int16_t and then mod it with IDX_MOD
*/
int16_t		get_idx_val(int16_t val)
{
	return (val % IDX_MOD);
}

void		print_verbosity_four_vals(t_process *process)
{
	int num_params;
	int	i;

	num_params = get_num_params(process->op);
	i = 0;
	while (num_params--)
	{
		if (process->param_type[i] == REG_CODE)
			ft_putchar('r');
		if (process->param_type[i] == IND_CODE)
			ft_printf("%hd", get_idx_val((int16_t)process->param_val[i]));
		else
			ft_printf("%d", process->param_val[i]);
		if (num_params > 0)
			ft_putchar(' ');
		i++;
	}
}
