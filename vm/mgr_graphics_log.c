/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_log.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void					render_data(t_graphics *g, t_env *e)
{
	if (!g->i)
		mvwprintw(g->game_window, 14 + g->i * 6, 193, AVATAR_NEO);
	else
		mvwprintw(g->game_window, 14 + g->i * 6, 193, AVATAR_SMITH);
	mvwprintw(g->game_window, 15 + g->i * 6, 193, "Player Name  : ");
	mvwprintw(g->game_window, 15 + g->i * 6, 210, "%s",
		e->new_player->name);
	mvwprintw(g->game_window, 16 + g->i * 6, 193,
		"Player ID    : ");
	mvwprintw(g->game_window, 16 + g->i * 6, 210, "%zu",
		e->new_player->prog_num);
	mvwprintw(g->game_window, 17 + g->i * 6, 193, "Last Live    : ");
	mvwprintw(g->game_window, 17 + g->i * 6, 210, "%ld",
		e->new_player->last_live);
	mvwprintw(g->game_window, 18 + g->i * 6, 193, "CurrentPeriod: ");
	mvwprintw(g->game_window, 18 + g->i * 6, 210, "%i",
		e->new_player->lives);
}

void					render_log(t_graphics *g, t_env *e)
{
	g->i = -1;
	g->j = -1;
	g->player_match = false;
	e->new_player = e->lst_players;
	while(++g->i < MAX_PLAYERS && g->player_id_init[g->i])
	{
		wattron(g->game_window, g->player_colors[g->i]);
		render_data(g, e);
		wattroff(g->game_window, g->player_colors[g->j]);
		e->new_player = e->new_player->next;
	}
}
