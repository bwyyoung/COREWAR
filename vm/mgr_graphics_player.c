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

void					render_player(t_graphics *g, t_env *e)
{

	if (e->prog_num_board[g->window_index] == 0xFFFFFFFF)
		wattron(g->game_window, COLOR_PAIR(GREEN_PAIR));
	else if (e->prog_num_board[g->window_index] == 0xFFFFFFFE)
		wattron(g->game_window, COLOR_PAIR(RED_PAIR));
	else if (e->prog_num_board[g->window_index] == 0xFFFFFFFD)
		wattron(g->game_window, COLOR_PAIR(YELLOW_PAIR));
	else if (e->prog_num_board[g->window_index] == 0xFFFFFFFC)
		wattron(g->game_window, COLOR_PAIR(MAGENTA_PAIR));
	else
	{
		wattroff(g->game_window, COLOR_PAIR(GREEN_PAIR));
		wattroff(g->game_window, COLOR_PAIR(RED_PAIR));
		wattroff(g->game_window, COLOR_PAIR(YELLOW_PAIR));
		wattroff(g->game_window, COLOR_PAIR(MAGENTA_PAIR));
	}
}
