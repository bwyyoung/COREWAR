/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/29 17:27:27 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*lst_players_add(t_env *e, t_player *p)
{
	e->new_player = e->lst_players;
	if (!e->lst_players)
	{
		e->lst_players = p;
		e->lst_players->next = NULL;
		e->lst_players->prev = NULL;
		// e->num_players += 1;
		return (e->lst_players);
	}
	while (e->new_player->next != NULL)
		e->new_player = e->new_player->next;
	e->new_player->next = p;
	p->prev = e->new_player;
	p->next = NULL;
	// e->num_players += 1;
	return (e->new_player);
}

void		lst_players_del(t_env *e, t_player *p)
{
	e->new_player = e->lst_players;
	if (!e->lst_players)
		return ;
	while (e->new_player != NULL)
	{
		if (e->new_player == p)
		{
			SAFE_DELETE(e->new_player->name);
			SAFE_DELETE(e->new_player->comment);
			if (e->new_player->prev)
				e->new_player->prev->next = e->new_player->next;
			if (e->new_player->next)
				e->new_player->next->prev = e->new_player->prev;
			if (e->new_player == e->lst_players)
				e->lst_players = e->lst_players->next;
			SAFE_DELETE(e->new_player);
			// e->num_players--;
			return ;
		}
		e->new_player = e->new_player->next;
	}
}

void		lst_players_clr(t_env *e)
{
	t_player			*current;

	if (!e->lst_players)
		return ;
	while (e->lst_players != NULL)
	{
		current = e->lst_players;
		e->lst_players = e->lst_players->next;
		SAFE_DELETE(current->name);
		SAFE_DELETE(current->comment);
		SAFE_DELETE(current);
	}
}

// int			lst_players_len(t_player *lst)
// {
// 	int			i;
// 	t_player	*tmp;

// 	i = 0;
// 	tmp = lst;
// 	if (tmp)
// 	{
// 		while (tmp)
// 		{
// 			tmp = tmp->next;
// 			i++;
// 		}
// 	}
// 	return (i);
// }
