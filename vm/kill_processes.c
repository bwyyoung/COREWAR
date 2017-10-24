/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/24 13:27:28 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			del_node(t_env *env, t_list *processes)
{
	env->num_processes--;
	// ft_printf("del_node %s %i\n", ((t_process*)processes->content)->name, env->num_processes);
	SAFE_DELETE(processes->content);
	//SAFE_DELETE(((t_process*)processes->content)->name);
	SAFE_DELETE(processes);
}

t_list			*kill_processes(t_env *env)
{
	t_list		*processes;
	t_list		*tmp;
	t_process	*process;
	t_list		*prev;

	// ft_printf("kill_processes 1\n");

	processes = env->processes;
	prev = NULL;
	while (processes)
	{
		process = (t_process*)processes->content;
		if (process->lives == 0)
		{
			// ft_printf("kill_processes 2\n");
			tmp = processes; //bad guy
			if (prev)
				prev->next = tmp->next;
			processes = processes->next;
			if (prev == NULL)//deleting first element
				env->processes = env->processes->next;
			del_node(env, tmp);
		}
		else
		{
			process->lives = 0;
			prev = processes;
			processes = processes->next;
		}
	}
	// ft_printf("kill_processes 3 %i %i\n", ft_lstlen(env->processes), env->num_processes);

	return (env->processes);
}
