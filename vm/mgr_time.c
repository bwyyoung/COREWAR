/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

dword			GetTickCount()
{
	struct timespec		ts;
	dword				theTick;

	theTick= 0U;
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts.tv_sec = mts.tv_sec;
	ts.tv_nsec = mts.tv_nsec;
	theTick  = (ts.tv_nsec / 1000000);
	theTick += (ts.tv_sec * 1000);
	return theTick;
}

void					graphics_print_message(t_graphics *g, char *str)
{
	if (!g->graphics_end)
		mvwprintw(g->game_window, 0,0 , str);
}

void					update_app(t_graphics *g, t_env *env)
{
	if (env->cycles_since_check >= env->cycle_to_die)
		perform_check(env);
	if (env->lst_process == NULL)
	{
		g->app_is_running = false;
		return ;
	}
	if (env->options[d] == 1 && env->dump_value == env->total_cycles)
	{
		dump_memory(env);
		g->app_is_running = false;
		return ;
	}
	if (env->options[s] == 1 && (env->total_cycles % env->cycle_value) == 0)
		dump_memory(env);
	execute_cycle(env);
	env->total_cycles++;
	env->cycles_since_check++;
}

void					display_app(t_graphics *g, t_env *e)
{
	render_start(g);
	if (g->seconds2 > MAT_REFRESH_RATE && (!g->mgr_cutscene.is_scene_playing))
	{
		werase(g->background_window);
		g->seconds2 = 0;
		loop_matrix(g, g->background_window, g->flag, g->col);
	}
	if ((!g->mgr_cutscene.is_scene_playing))
	{
		render_board(g, e);
		render_process(g, e);
	}
	else
		render_cutscene(g);
	render_stats(g, e);
	render_log(g, e);
	render_end(g);
}
