/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/16 16:35:07 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		free_node(t_list *node)
{
	free(node->content);
	free(node);
}

t_list			*kill_processes(t_env *env)
{
	t_list		*processes;
	t_list		*tmp;
	t_list		**pointer_mover;
	t_process	*process;

	pointer_mover = &env->processes;
	processes = env->processes;
	while (processes)
	{
		process = (t_process*)processes->content;
		if (process->lives == 0)
		{
			tmp = processes;
			*pointer_mover = processes->next;
			free_node(tmp);
		}
		else
		{
			process->lives = 0;
			pointer_mover = &processes->next;
		}
		processes = processes->next;
	}
	return (env->processes);
}
