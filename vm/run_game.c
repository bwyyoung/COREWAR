/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 18:26:54 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

void		perform_check(t_env *env)
{
	if (env->lives_since_check >= NBR_LIVE || env->checks == MAX_CHECKS - 1)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		env->checks = 0;
	}
	else
		env->checks++;
	env->cycles_since_check = 0;
	env->lives_since_check = 0;
	kill_processes(env);
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
	g->line_colors[0] = COLOR_GREEN;
	g->line_colors[1] = 0;
	g->line_colors[2] = GREEN_PAIR;
	g->title_colors[0] = COLOR_YELLOW;
	g->title_colors[1] = 0;
	g->title_colors[2] = YELLOW__PAIR;
	return (g);
}

void		graphics_loop(t_env *e)
{
	t_graphics		*g;

	g = init_graphics(e);
	Graphics_Start(g);
	while (g->app_is_running)
	{
		g->current = GetTickCount();
		g->elapsed = g->current - g->start_time;
		g->seconds += g->elapsed;
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
	Graphics_End(g);
}
