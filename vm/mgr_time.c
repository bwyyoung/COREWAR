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

DWORD			GetTickCount()
{
	struct timespec		ts;
	DWORD				theTick;

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

void					update_app(t_graphics *g, t_env *e)
{
	(void)g;
	(void)e;
}

void					display_app(t_graphics *g, t_env *e)
{
	(void)e;
	Render_Start(g);
	Render_End(g);
}
