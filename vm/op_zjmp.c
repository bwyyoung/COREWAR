/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/02 20:34:39 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual],
		"P %4u | zjmp %hd ", process->process_num, process->param_val[0]);
	if (process->carry == 1)
		P(env->g_ref, env->options[visual], "OK\n");
	else
		P(env->g_ref, env->options[visual], "FAILED\n");
}

/*
** If the carry == 1 zjmp will increase the pc of the
** process by the idx_val of its only param
** else it will do nothing but inc its pc to skip the jmp
** instruction and its parameter.
*/

void		op_zjmp(t_env *env, t_process *process)
{
	(void)env;
	if (process->carry == 1)
		inc_pc(process, (int16_t)process->param_val[0] % IDX_MOD);
	else
		inc_pc(process, 1 + IND_SIZE);
	print_verbosity_four(env, process);
}
