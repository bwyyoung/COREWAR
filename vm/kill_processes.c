/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/24 18:25:01 by dengstra         ###   ########.fr       */
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

void			kill_processes(t_env *env)
{
	t_process	*process_iter;
	t_process	*cur_process;

	process_iter = env->lst_process;
	while (process_iter)
	{
		cur_process = process_iter;
		if (cur_process->lives == 0)
		{
			process_iter = process_iter->next;
			lst_process_del(env, cur_process);
			cur_process = NULL;
		}
		else
		{
			cur_process->lives = 0;
			process_iter = process_iter->next;
		}
	}
	//if (!lst_process_len(env->lst_process))
	//	exit(1);
}
