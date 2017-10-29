/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/28 18:11:20 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"
#include <locale.h>

void		perform_check(t_env *env)
{
	kill_processes(env);
	if (env->lives_since_check >= NBR_LIVE || env->checks == MAX_CHECKS - 1)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if (env->options[v] && env->verbose_value == 2)
			P(env->options[visual], "Cycle to die is now %d\n", env->cycle_to_die);
		env->checks = 0;
	}
	else
		env->checks++;
	env->cycles_since_check = 0;
	env->lives_since_check = 0;
}

/*
** This is the main game loop.
** The game ends when all of the processes have died (env->processes == NULL)
** Every time cycles_since_check is >= cycle_to_die we have to
** perform check. During the check all the processes that didn't execute the
** live command will be deleted.
*/
void		run_game(t_env *env)
{
	while (1)
	{
		if (env->cycles_since_check >= env->cycle_to_die)
			perform_check(env);
		if (env->lst_process == NULL)
			break;
		if (env->options[d] == 1 && env->dump_value == env->total_cycles)
		{
			dump_memory(env);
			break;
		}
		if (env->options[s] == 1 && (env->total_cycles % env->cycle_value) == 0)
			dump_memory(env);
		execute_cycle(env);
		env->total_cycles++;
		env->cycles_since_check++;
		if (env->options[v] && env->verbose_value == 2)
			P(env->options[visual], "It is now cycle %d\n", env->total_cycles);
	}
}

t_graphics	*init_graphics(t_env *e)
{
	t_graphics		*g;

	g = (t_graphics *)malloc(sizeof(t_graphics));
	if (!g)
		error_exit(e, 22);
	g->start_time = GetTickCount();
	g->next_app_tick = g->start_time;
	g->sleep_time = 0;
	g->seconds = 0;
	g->app_is_running = t_true;
	g->margin_x = 2;
	g->margin_y = 2;
	g->graphics_end = t_false;
	g->offsetx = (COLS - WORLD_WIDTH) / 2;
	g->offsety = (LINES - WORLD_HEIGHT) / 2;
	initscr();
	noecho();
	refresh();
	curs_set(FALSE);
	return (g);
}

void		graphics_loop(t_env *e)
{
	t_graphics		*g;

	setlocale(LC_ALL, "");
	g = init_graphics(e);
	graphics_start(g);
	while (g->app_is_running)
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
		g->next_app_tick += SKIP_TICKS;
		g->sleep_time = (g->next_app_tick - GetTickCount());
		if (g->sleep_time >= 0)
			usleep((useconds_t)g->sleep_time);
		g->start_time = g->current;
	}
	graphics_end(g);
}
