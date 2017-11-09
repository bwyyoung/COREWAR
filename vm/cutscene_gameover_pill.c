/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_gameover_pill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			render_header(t_graphics *g, t_cutscene *thescene)
{
	wattron(g->dialog_window, COLOR_PAIR(GREEN_PAIR));
	thescene->index = -1;
	if (!thescene->current)
		return ;
	while (++thescene->index < CUTSCENE_HEIGHT)
		if (thescene->current->frame[thescene->index])
			mvwprintw(g->dialog_window, thescene->index + 5, 1, "%s",
				thescene->current->frame[thescene->index]);
	mvwprintw(g->dialog_window, 60,
		55, "[ENTER] \"Stay in Wonderland\"");
	mvwprintw(g->dialog_window, 60,
		189, "[ESC] \"The Story Ends...\"");
	wattroff(g->dialog_window, COLOR_PAIR(GREEN_PAIR));
}

void			render_pill2(t_graphics *g, int y, int x, chtype c)
{
	t_scene_frame	*next;

	next = g->mgr_cutscene.pill->current->next;
	wattron(g->dialog_window, c);
	g->mgr_cutscene.pill->index = -1;
	if (!next)
		next = g->mgr_cutscene.pill->animation;
	while (++g->mgr_cutscene.pill->index < CUTSCENE_HEIGHT)
		if (next->frame[g->mgr_cutscene.pill->index])
			mvwprintw(g->dialog_window, g->mgr_cutscene.pill->index + y,
				x, "%s",
				next->frame[g->mgr_cutscene.pill->index]);
	wattroff(g->dialog_window, c);
}

void			render_pill(t_graphics *g, int y, int x, chtype c)
{
	wattron(g->dialog_window, c);
	g->mgr_cutscene.pill->index = -1;
	if (!g->mgr_cutscene.pill->current)
		g->mgr_cutscene.pill->current = g->mgr_cutscene.pill->animation;
	while (++g->mgr_cutscene.pill->index < CUTSCENE_HEIGHT)
		if (g->mgr_cutscene.pill->current->frame[g->mgr_cutscene.pill->index])
			mvwprintw(g->dialog_window, g->mgr_cutscene.pill->index + y, x
				, "%s",
			g->mgr_cutscene.pill->current->frame[g->mgr_cutscene.pill->index]);
	wattroff(g->dialog_window, c);
}

void			render_game_over(t_graphics *g)
{
	wattron(g->dialog_window, COLOR_PAIR(GREEN_PAIR));
	if (g->seconds2 > APP_REFRESH_RATE)
	{
		werase(g->background_window);
		g->seconds2 = 0;
		loop_matrix(g, g->background_window, g->flag, g->col);
	}
	box(g->dialog_window, 0, 0);
	render_pill(g, 50, 60, COLOR_PAIR(RED_PAIR));
	render_pill2(g, 50, 194, COLOR_PAIR(CYAN_PAIR));
	render_header(g, g->mgr_cutscene.current_cutscene);
	if (g->key_pressed == APP_KEY_ENTER)
		g->restart = true;
	if (g->seconds3 <= MAT_REFRESH_RATE)
		return ;
	g->seconds3 = 0;
	g->mgr_cutscene.pill->current = g->mgr_cutscene.pill->current->next;
}
