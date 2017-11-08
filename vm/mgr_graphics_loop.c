/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/08 17:11:14 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

void		graphics_loop_start(t_graphics *g, t_env *e)
{
	g->current = GetTickCount();
	g->elapsed = g->current - g->start_time;
	g->seconds += g->elapsed;
	g->seconds2 += g->elapsed;
	if (g->mgr_cutscene.is_scene_playing)
		g->seconds3 += g->elapsed;
	if (g->mgr_cutscene.is_dialog_playing)
		g->seconds4 += g->elapsed;
	get_keyboard_event(g);
	if (g->seconds <= APP_REFRESH_RATE)
		return ;
	g->seconds = 0;
	if (!g->mgr_cutscene.is_scene_playing)
		if  (!g->mgr_cutscene.is_dialog_playing)
			update_app(g, e);
	display_app(g, e);
}

void 		graphics_loop_end(t_graphics *g)
{
	g->next_app_tick += SKIP_TICKS;
	g->sleep_time = (g->next_app_tick - GetTickCount());
	if (g->sleep_time >= 0)
		usleep((useconds_t)g->sleep_time);
	g->start_time = g->current;
}

void		graphics_loop(t_env *e, t_env *backup)
{
	t_graphics		*g;

	UNUSED(backup);
	g = init_graphics(e);
	graphics_start(g);
	init_cutscenes(&g->mgr_cutscene);
	init_player_colors(g, e);
	introduce_players(e);
	play_dialog(g, g->mgr_cutscene.dialog_intro);
	while (g->app_is_running)
	{
		graphics_loop_start(g, e);
		graphics_loop_end(g);
	}
	destroy_cutscenes(&g->mgr_cutscene);
	graphics_end(g);
}
