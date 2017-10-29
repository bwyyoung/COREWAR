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
		wattroff(g->game_window, COLOR_PAIR(GREEN_PAIR));
		wattroff(g->game_window, COLOR_PAIR(RED_PAIR));
		wattroff(g->game_window, COLOR_PAIR(YELLOW_PAIR));
		wattroff(g->game_window, COLOR_PAIR(MAGENTA_PAIR));
		if (e->new_process->prog_num == 0xFFFFFFFF)
			wattron(g->game_window, COLOR_PAIR(GREEN_PAIR));
		else if (e->new_process->prog_num == 0xFFFFFFFE)
			wattron(g->game_window, COLOR_PAIR(RED_PAIR));
		else if (e->new_process->prog_num == 0xFFFFFFFD)
			wattron(g->game_window, COLOR_PAIR(YELLOW_PAIR));
		else if (e->new_process->prog_num == 0xFFFFFFFC)
			wattron(g->game_window, COLOR_PAIR(MAGENTA_PAIR));
		g->window_y = e->new_process->regs[0] / BOARD_WIDTH;
		g->window_x = e->new_process->regs[0] % BOARD_WIDTH;
		mvwprintw(g->game_window, g->window_y,
			g->window_x * 2 + g->window_x, "%02X",
			e->board[e->new_process->regs[0]]);
		e->new_process = e->new_process->next;
	}
	wattroff(g->game_window, A_REVERSE);
}
