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
	t_list *new_node;

	if (!(new_node = ft_lstnew(new_process, sizeof(t_process))))
		ft_error_errno(NULL);
	ft_lstadd(&env->processes, new_node);
	env->num_processes++;
}

