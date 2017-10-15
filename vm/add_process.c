/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:20:09 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/12 15:12:16 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_process(t_env *env, t_process *process)
{
	t_list *processes;

	processes = ft_lstnew(process, sizeof(t_process));// unprotected
	ft_lstadd(&env->processes, processes);
	env->num_processes++;
}
