/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_verbosity_sixteen.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/27 13:44:03 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_verbosity_sixteen(t_env *env, t_process *process, int inc)
{
	uint32_t i;
	uint32_t op_size;

	if (!env->options[v] || env->verbose_value != 16 || inc < 2
		|| (process->carry && process->op == zjmp))
		return ;
	ft_printf("ADV %d (0x%04x -> 0x%04x) %02x %02x ", inc, process->regs[0],
			(process->regs[0] + inc) % MEM_SIZE, process->op, process->types);
	i = 2;
	op_size = get_op_size(process);
	while (i < op_size)
	{
		ft_printf("%02x ", get_board_val(env->board, process->regs[0] + i, 1));
		i++;
	}
	ft_putchar('\n');
}
