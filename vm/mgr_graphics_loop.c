/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/29 16:51:54 by dengstra         ###   ########.fr       */
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
	get_keyboard_event(g);
	if (g->seconds > APP_REFRESH_RATE)
	{
		g->seconds = 0;
		update_app(g, e);
		display_app(g, e);
	}
}

void 		graphics_loop_end(t_graphics *g)
{
	g->next_app_tick += SKIP_TICKS;
	g->sleep_time = (g->next_app_tick - GetTickCount());
	if (g->sleep_time >= 0)
		usleep((useconds_t)g->sleep_time);
	g->start_time = g->current;
}

void		graphics_loop(t_env *e)
{
	t_graphics		*g;

	g = init_graphics(e);
	snd_play_background_music(&g->mgr_cutscene);
	while (g->app_is_running)
	{
		graphics_loop_start(g, e);
		graphics_loop_end(g);
	}
	graphics_end(g);
}
