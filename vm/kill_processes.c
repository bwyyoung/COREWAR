/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/23 11:11:28 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			del_node(t_env *env, t_list *processes, t_list *prev)
{
	if (!prev)
		env->processes = processes->next;
	else
		prev->next = processes->next;
	env->num_processes--;
	SAFE_DELETE(processes->content);
	SAFE_DELETE(processes);
}

t_list			*kill_processes(t_env *env)
{
	t_list		*processes;
	t_list		*tmp;
	t_process	*process;
	t_list		*prev;

	processes = env->processes;
	prev = NULL;
	while (processes)
	{
		process = (t_process*)processes->content;
		if (process->lives == 0)
		{
			tmp = processes->next;
			del_node(env, processes, prev);
			processes = tmp;
		}
		else
		{
			process->lives = 0;
			prev = processes;
			processes = processes->next;
		}
	}
	return (env->processes);
}
