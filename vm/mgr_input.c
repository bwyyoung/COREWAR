/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

bool					keyboard_event()
{
	int		ch;

	ch = getch();
	if (ch == ERR)
		return t_false;
	ungetch(ch);
	return t_true;
}

void 					quit_graphics(t_graphics *g)
{
	g->app_is_running = t_false;
}

void					get_keyboard_event(t_graphics *g)
{
	g->key_pressed = -1;
	if (!keyboard_event())
		return ;
	g->key_pressed = getch();
	if (g->key_pressed == APP_KEY_SPACE)
		return ;
	else if (g->key_pressed != APP_KEY_ESC)
		return ;
	if (getch() != APP_KEY_SPECIAL)
		quit_graphics(g);
	g->key_pressed = getch();
	if (g->key_pressed == APP_KEY_UP)
		return ;
	else if (g->key_pressed == APP_KEY_DOWN)
		return ;
	else if (g->key_pressed == APP_KEY_LEFT)
		return ;
	else if (g->key_pressed == APP_KEY_RIGHT)
		return ;
}
