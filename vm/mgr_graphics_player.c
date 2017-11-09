/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void					init_player_colors(t_graphics *g, t_env *e)
{
	g->i = -1;
	while(++g->i < MAX_PLAYERS)
	{
		g->player_id_init[g->i] = false;
		g->player_id[g->i] = 0;
	}
	g->player_colors[0] = COLOR_PAIR(GREEN_PAIR);
	g->player_colors[1] = COLOR_PAIR(RED_PAIR);
	g->player_colors[2] = COLOR_PAIR(YELLOW_PAIR);
	g->player_colors[3] = COLOR_PAIR(MAGENTA_PAIR);
	g->i = -1;
	e->new_player = e->lst_players;
	while(++g->i < e->num_players)
	{
		g->player_id_init[g->i] = true;
		g->player_id[g->i] = e->new_player->prog_num;
		e->new_player = e->new_player->next;
	}
}

void					render_player(t_graphics *g, uint32_t pn)
{
	g->i = -1;
	g->j = -1;
	g->player_match = false;
	while(++g->i < MAX_PLAYERS && g->player_id_init[g->i])
	{
		if (pn != g->player_id[g->i])
			continue ;
		g->player_match = true;
		wattron(g->game_window, g->player_colors[g->i]);
		break;
	}
	if (g->player_match)
		return ;
	while(++g->j < MAX_PLAYERS && g->player_id_init[g->j])
		wattroff(g->game_window, g->player_colors[g->j]);
}
