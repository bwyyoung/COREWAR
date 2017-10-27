/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_board.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void					Render_Board(t_graphics *g, t_env *e)
{
	(void)e;
	g->window_x = 0;
	g->window_y = 0;
	g->window_index = -1;
	while (g->window_index++ < MEM_SIZE)
	{
		if (g->window_x >= BOARD_WIDTH)
		{
			g->window_x = 0;
			g->window_y++;
		}
		//mvwprintw(g->game_window, g->window_y,
		//	g->window_x * 2 + g->window_x, ft_itoa_base(
		//		e->board[g->window_index], 16));
		g->window_x++;
	}
}
