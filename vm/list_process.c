/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/10 12:12:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		lst_process_add(t_env *e, t_process *p)
{
	e->new_process = e->lst_process;
	if (!e->lst_process)
	{
		e->lst_process = p;
		e->lst_process->next = NULL;
		e->lst_process->prev = NULL;
	}
	else
	{
		p->next = e->lst_process;
		e->lst_process->prev = p;
		e->lst_process = p;
	}
	e->num_processes++;
	e->total_num_processes++;
}

void		lst_process_del(t_env *e, t_process *p)
{
	e->new_process = e->lst_process;
	if (!e->lst_process)
		return ;
	while (e->new_process != NULL)
	{
		if (e->new_process == p)
		{
			if (e->new_process->prev)
				e->new_process->prev->next = e->new_process->next;
			if (e->new_process->next)
				e->new_process->next->prev = e->new_process->prev;
			if (e->new_process == e->lst_process)
				e->lst_process = e->lst_process->next;
			SAFE_DELETE(e->new_process);
			e->num_processes--;
			return ;
		}
		e->new_process = e->new_process->next;
	}
}

void		lst_process_clr(t_env *e)
{
	t_process			*current;

	if (!e->lst_process)
		return ;
	while (e->lst_process != NULL)
	{
		current = e->lst_process;
		e->lst_process = e->lst_process->next;
		SAFE_DELETE(current);
	}
}

int			lst_process_len(t_process *lst)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = lst;
	if (tmp)
	{
		while (tmp)
		{
			tmp = tmp->next;
			i++;
		}
	}
	return (i);
}
