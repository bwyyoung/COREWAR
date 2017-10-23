/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:20:09 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/16 17:05:56 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_process(t_env *env, t_process *new_process)
{
	ft_printf("add_process 1\n");
	t_list *new_node;

	if (!(new_node = ft_lstnew(new_process, sizeof(t_process))))
		ft_error_errno(NULL);
	if (!env->processes)
	{
		ft_printf("add_process 2\n");
		env->processes = new_node;
	}
	else
	{
		ft_printf("add_process 3\n");

		//env->element = env->processes;
		//while (env->element->next != NULL)
		//	env->element = env->element->next;
		ft_lstadd(&env->processes, new_node);
	}
	env->num_processes++;
	ft_printf("add_process %i %i\n", ft_lstlen(env->processes), env->num_processes);
}
