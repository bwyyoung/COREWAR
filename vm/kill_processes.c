/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:47:27 by douglas           #+#    #+#             */
/*   Updated: 2017/10/26 11:17:59 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
			env->lst_process = curr->next;
			SAFE_DELETE(curr);
			curr = env->lst_process;
		}
		else if (curr->lives == 0)
		{
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
