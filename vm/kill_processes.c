/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/11/04 19:55:08 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_verbosity_eight(t_env *env, t_process *process)
{
	if (env->options[v] && env->verbose_value == 8)
		P(env->g_ref, env->options[visual],
			"Process %d hasn't lived for %d cycles (CTD %d)\n",
				process->process_num, process->last_live, env->cycle_to_die);
}

void		print_and_delete(t_env *env, t_process *curr, t_process *prev)
{
	if (prev == NULL)
		env->lst_process = curr->next;
	print_verbosity_eight(env, curr);
	SAFE_DELETE(curr);
}

void		kill_processes(t_env *env)
{
	t_process	*curr;
	t_process	*prev;

	curr = env->lst_process;
	prev = NULL;
	while (curr)
	{
		if ((curr->lives == 0 || env->cycle_to_die < 0) && prev == NULL)
		{
			print_and_delete(env, curr, prev);
			curr = env->lst_process;
		}
		else if (curr->lives == 0 || env->cycle_to_die < 0)
		{
			prev->next = curr->next;
			print_and_delete(env, curr, prev);
			curr = prev->next;
		}
		else
		{
			curr->lives = 0;
			prev = curr;
			curr = curr->next;
		}
	}
}
