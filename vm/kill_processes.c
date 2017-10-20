/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/20 10:35:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			free_node(t_list *node)
{
	SAFE_DELETE(node->content);
	SAFE_DELETE(node);
}

/*
** Linus Torvalds double pointer
*/
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
