/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_verbosity_sixteen.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/28 16:54:55 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_verbosity_sixteen(t_env *env, t_process *process, int inc, int pc)
{
	int i;

	if (!env->options[v] || env->verbose_value != 16 || inc < 2
		|| (process->carry && process->op == zjmp))
		return ;
	P(env->g_ref, env->options[visual], "ADV %d (0x%04x -> 0x%04x) %02x %02x ", inc, pc,
			pc + inc, process->op, process->types);
	i = 2;
	while (i < inc)
	{
		P(env->g_ref, env->options[visual], "%02x ", get_board_val(env->board, pc + i, 1));
		i++;
	}
	ft_putchar('\n');
}
