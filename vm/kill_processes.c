/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/28 14:01:29 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_verbosity_eight(t_env *env, t_process *process)
{
	if (env->options[v] && env->verbose_value == 8)
		P(env->options[visual],
			"Process %d hasn't lived for %d cycles (CTD %d)\n",
				process->process_num, process->last_live, env->cycle_to_die);
}

void		kill_processes(t_env *env)
{
	t_process *curr;
	t_process *prev;

	curr = env->lst_process;
	prev = NULL;
	while (curr)
	{
		if (curr->lives == 0 && prev == NULL)
		{
			print_verbosity_eight(env, curr);
			env->lst_process = curr->next;
			SAFE_DELETE(curr);
			curr = env->lst_process;
		}
		else if (curr->lives == 0)
		{
			print_verbosity_eight(env, curr);
			prev->next = curr->next;
			SAFE_DELETE(curr);
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
