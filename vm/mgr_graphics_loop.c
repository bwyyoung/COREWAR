/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

void		graphics_loop_start(t_graphics *g, t_env *e)
{
	g->current = gettickcount();
	g->elapsed = g->current - g->start_time;
	g->seconds += g->elapsed;
	g->seconds2 += g->elapsed;
	if (g->mgr_cutscene.is_scene_playing ||
		(g->game_over && g->init_game_over_menu))
		g->seconds3 += g->elapsed;
	if (g->mgr_cutscene.is_dialog_playing)
		g->seconds4 += g->elapsed;
	if (g->seconds <= APP_REFRESH_RATE)
		return ;
	g->seconds = 0;
	if (!g->mgr_cutscene.is_scene_playing)
		if (!g->mgr_cutscene.is_dialog_playing)
			if (!g->game_over)
				update_app(g, e);
}

void		graphics_loop_end(t_graphics *g)
{
	g->next_app_tick += SKIP_TICKS;
	g->sleep_time = (g->next_app_tick - gettickcount());
	if (g->sleep_time >= 0)
		usleep((useconds_t)g->sleep_time);
	g->start_time = g->current;
}

void		game_intro(t_env *e, t_graphics *g, int delay)
{
	clear();
	if (ENABLE_SOUND)
		snd_delete_playing_audio(&g->mgr_cutscene);
	g->game_over = false;
	g->init_game_over_menu = false;
	g->restart = false;
	introduce_players(e);
	if (!g->game_over)
		play_dialog(g, g->mgr_cutscene.dialog_intro, delay);
}

void		graphics_loop(t_env *e, t_env *backup)
{
	t_graphics		*g;

	UNUSED(backup);
	g = init_graphics(e);
	graphics_start(g);
	init_cutscenes(&g->mgr_cutscene);
	init_player_colors(g, e);
	game_intro(e, g, -1500);
	while (g->app_is_running)
	{
		get_keyboard_event(g);
		if (!g->app_is_running)
			break ;
		graphics_loop_start(g, e);
		display_app(g, e);
		graphics_loop_end(g);
		game_over(g, e);
		if (!g->restart)
			continue ;
		cpy_env(e, backup);
		game_intro(e, g, -800);
	}
	destroy_cutscenes(&g->mgr_cutscene);
	graphics_end(g);
}
