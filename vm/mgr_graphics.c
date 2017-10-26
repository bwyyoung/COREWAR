/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void					Graphics_Start(t_graphics *g)
{
	g->margin_x = 2;
	g->margin_y = 2;
	g->graphics_end = t_false;
	initscr();
	noecho();
	refresh();
	curs_set(FALSE);
	g->offsetx = (COLS - WORLD_WIDTH) / 2;
	g->offsety = (LINES - WORLD_HEIGHT) / 2;
	g->border_window = newwin(WORLD_HEIGHT + 2, WORLD_WIDTH + 2,
	g->offsety - 1, g->offsetx - 1);
	g->game_window = newwin(WORLD_HEIGHT, WORLD_WIDTH, g->offsety, g->offsetx);
	getmaxyx(stdscr, g->max_y, g->max_x);
	cbreak();
	nodelay(stdscr, TRUE);
	start_color();
	box(g->border_window, 0 , 0);
	wrefresh(g->border_window);
	init_pair(g->title_colors[2], g->title_colors[0], g->title_colors[1]);
	init_pair(g->line_colors[2], g->line_colors[0], g->line_colors[1]);
	init_pair(10, 7, 0);
	wattron(g->game_window, COLOR_PAIR(10));
}

void					Graphics_End(t_graphics *g)
{
	g->graphics_end = t_true;
	delwin(g->game_window);
	delwin(g->border_window);
	endwin();
	SAFE_DELETE(g);
}

void					Render_Start(t_graphics *g)
{
	g->i = -1;
	g->j = -1;
	while (++g->i < WORLD_WIDTH)
		while (++g->j < WORLD_HEIGHT)
			mvwprintw(g->game_window, g->j, g->i, " ");
}

void					Render_End(t_graphics *g)
{
	wattron(g->game_window, COLOR_PAIR(10));
	wrefresh(g->game_window);
}
