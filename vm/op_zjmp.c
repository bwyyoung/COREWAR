/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:21:37 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/27 17:37:43 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | zjmp %hd ", process->process_num,
									process->param_val[0]);
	if (process->carry == 1)
		P(env->g_ref, env->options[visual], "OK\n");
	else
		P(env->g_ref, env->options[visual], "FAILED\n");
}

/*
** If the carry == 1 zjmp will increase the pc of the process by the idx_val of its
** only param
** else it will do nothing but inc its pc to skip the jmp instruction and its parameter.
*/

void	op_zjmp(t_env *env, t_process *process)
{
	(void)env;
	if (process->carry == 1)
		inc_pc(process, get_idx_val((int16_t)process->param_val[0]));
	else
		inc_pc(process, 1 + IND_SIZE);
	print_verbosity_four(env, process);
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
