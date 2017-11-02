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

# define ACTUAL_BOARD (BOARD_WIDTH * 2 + BOARD_WIDTH)

void					graphics_start(t_graphics *g)
{
	initscr();
	noecho();
	refresh();
	curs_set(FALSE);
	g->margin_x = 2;
	g->margin_y = 2;
	g->graphics_end = t_false;
	g->offsetx = (COLS - WORLD_WIDTH) / 2;
	g->offsety = (LINES - WORLD_HEIGHT) / 2;
	init_matrix(&g->background_window, &g->mat);
	g->border_window = newwin(WORLD_HEIGHT + 2, WORLD_WIDTH + 2,
	g->offsety - 1, g->offsetx - 1);
	g->game_window = newwin(WORLD_HEIGHT, WORLD_WIDTH, g->offsety, g->offsetx);
	getmaxyx(stdscr, g->max_y, g->max_x);
	g->video_window = newwin(WORLD_HEIGHT + 2, CUTSCENE_WIDTH + 2,
		g->offsety - 1, g->offsetx - 11);
	g->log_window = newwin(WORLD_HEIGHT / 2, WORLD_WIDTH - ACTUAL_BOARD,
	g->offsety + WORLD_HEIGHT / 2, g->offsetx + ACTUAL_BOARD);
	scrollok(g->log_window, TRUE);
	cbreak();
	nodelay(stdscr, TRUE);
}

void					graphics_end(t_graphics *g)
{
	g->graphics_end = t_true;
	delwin(g->video_window);
	delwin(g->log_window);
	delwin(g->game_window);
	delwin(g->border_window);
	delwin(g->background_window);
	endwin();
	g->mat->i = -1;
	while (++(g->mat->i) < g->mat->c / 2)
	{
		SAFE_DELETE(g->mat->cols[g->mat->i].rows);
	}
	SAFE_DELETE(g->mat->cols);
	SAFE_DELETE(g->mat);
	SAFE_DELETE(g);
}

void					render_start(t_graphics *g)
{
	g->i = -1;
	g->j = -1;
	werase(g->game_window);
	box(g->border_window, 0 , 0);
	box(g->log_window, 0 , 0);
}

void					render_end(t_graphics *g)
{
	wnoutrefresh(g->background_window);
	wnoutrefresh(g->border_window);
	wnoutrefresh(g->game_window);
	wnoutrefresh(g->log_window);
	//if (g->mgr_cutscene.is_scene_playing)
		wnoutrefresh(g->video_window);
	doupdate();
}
