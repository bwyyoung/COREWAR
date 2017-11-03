/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:31:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 20:21:43 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_verbosity_four(t_env *env, t_process *process,
										t_process *cpy, int op)
{
	if (env->options[v] && env->verbose_value == 4)
		P(env->g_ref, env->options[visual],
			"P %4u | %s %hd (%d)\n", process->process_num,
				env->op_tab[op].name, process->param_val[0], cpy->regs[0]);
}

/*
** Creates a new process. The new process will be the same except
** for the pc and cycles_left.
** The difference between fork and lfork is that fork will use a
** idx_val to increase the pc
** while lfork will just use the ind_val directly.
**
** T_DIR
*/

void			op_forker(t_env *env, t_process *process, int op)
{
	t_process	*cpy;

	cpy = create_process(env, NULL);
	ft_memcpy(cpy, process, sizeof(t_process));
	if (op == lfork)
		cpy->regs[0] += (int16_t)process->param_val[0];
	else
		cpy->regs[0] += (int16_t)process->param_val[0] % IDX_MOD;
	cpy->cycles_left = 0;
	cpy->process_num = env->num_processes + 1;
	lst_process_add(env, cpy);
	print_verbosity_four(env, process, cpy, op);
	cpy->regs[0] = get_board_pos(cpy->regs[0]);
}
