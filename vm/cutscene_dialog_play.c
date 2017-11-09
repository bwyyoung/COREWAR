/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_dialog_play.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/23 21:48:45 by byoung-w          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void 				forward_dialog_cutscene(t_graphics *g, t_cutscene *thescene)
{
	if (!thescene->current)
	{
		g->mgr_cutscene.is_scene_playing = false;
		if (ENABLE_SOUND)
			snd_delete_playing_audio(&g->mgr_cutscene);
		return ;
	}
	thescene->index = -1;
	while (++thescene->index < CUTSCENE_HEIGHT)
		if (thescene->current->frame[thescene->index])
			mvwprintw(g->dialog_window, thescene->index + 5, 1, "%s",
				thescene->current->frame[thescene->index]);
	thescene->index = -1;
}

void				forward_dialog(t_graphics *g, t_dialog *d)
{
	if (g->seconds4 > d->duration)
	{
		g->mgr_cutscene.is_dialog_playing = false;
		if (ENABLE_SOUND)
			snd_delete_playing_audio(&g->mgr_cutscene);
		d->finished(&g->mgr_cutscene);
		return ;
	}
	mvwprintw(g->dialog_window, 63, 80,
		g->mgr_cutscene.current_dialog->current->text);
	mvwprintw(g->dialog_window, 70, 220,
		"PRESS [ENTER] TO SKIP CUTSCENE");
}

void 				render_dialog(t_graphics *g)
{
	if (g->key_pressed == APP_KEY_ENTER)
		g->seconds4 = g->mgr_cutscene.current_dialog->duration + 100;
	wattron(g->dialog_window, COLOR_PAIR(GREEN_PAIR));
	box(g->dialog_window, 0 , 0);
	forward_dialog(g, g->mgr_cutscene.current_dialog);
	forward_dialog_cutscene(g, g->mgr_cutscene.current_cutscene);
	if (g->mgr_cutscene.current_dialog->current->next)
		if (g->mgr_cutscene.current_dialog->current->next->timestamp <
			g->seconds4)
		{
			g->mgr_cutscene.current_dialog->current = 
				g->mgr_cutscene.current_dialog->current->next;
			g->mgr_cutscene.current_cutscene->current =
				g->mgr_cutscene.current_cutscene->current->next;
		}
	wattroff(g->dialog_window, COLOR_PAIR(GREEN_PAIR));
}

void				play_dialog(t_graphics *g, t_dialog *d)
{
	prep_cutscene(g, d->video_file);
	if (ENABLE_SOUND)
		play_audio(&g->mgr_cutscene, start,
			g->mgr_cutscene.current_cutscene->sound_file, false);
	d->current = d->subtitle;
	g->seconds4 = -1500;
	g->mgr_cutscene.current_dialog = d;
	g->mgr_cutscene.is_dialog_playing = true;
}
