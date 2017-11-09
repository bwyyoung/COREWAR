/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void					render_process(t_graphics *g, t_env *e)
{
	e->new_process = e->lst_process;
	wattron(g->game_window, A_REVERSE);
	while (e->new_process)
	{
		render_player(g, e->new_process->prog_num);
		g->window_y = e->new_process->regs[0] / BOARD_WIDTH;
		g->window_x = e->new_process->regs[0] % BOARD_WIDTH;
		mvwprintw(g->game_window, g->window_y,
			g->window_x * 2 + g->window_x, "%02X",
			e->board[e->new_process->regs[0]]);
		e->new_process = e->new_process->next;
	}
	wattroff(g->game_window, A_REVERSE);
}
