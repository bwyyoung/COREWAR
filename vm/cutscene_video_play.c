/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_video_play.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/23 21:48:45 by byoung-w          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void					forward_cutscene(t_graphics *g, t_cutscene *thescene)
{
	if (!thescene->current)
	{
		g->mgr_cutscene.is_scene_playing = false;
		snd_delete_playing_audio(&g->mgr_cutscene);
		return ;
	}
	thescene->index = -1;
	while (++thescene->index < CUTSCENE_HEIGHT)
	{
		if (thescene->current->frame[thescene->index])
			mvwprintw(g->video_window, thescene->index + 5, 1, "%s",
			thescene->current->frame[thescene->index]);
	}
	thescene->index = -1;
	if (g->seconds3 > thescene->refresh_rate)
	{
		g->seconds3 = 0;
		thescene->current = thescene->current->next;
	}
}

void					render_cutscene(t_graphics *g)
{
	wattron(g->video_window, COLOR_PAIR(GREEN_PAIR));
	box(g->video_window, 0 , 0);
	forward_cutscene(g, g->mgr_cutscene.current_cutscene);
	wattroff(g->video_window, COLOR_PAIR(GREEN_PAIR));
}

void 					play_cutscene(t_graphics *g, char *name)
{
	g->mgr_cutscene.is_scene_playing = true;
	g->mgr_cutscene.current_cutscene = g->mgr_cutscene.cutscenes;
	while (g->mgr_cutscene.current_cutscene)
	{
		if (!ft_strcmp(name, g->mgr_cutscene.current_cutscene->video_file))
			break ;
		g->mgr_cutscene.current_cutscene =
			g->mgr_cutscene.current_cutscene->next;
	}
	if (!g->mgr_cutscene.current_cutscene)
		return ;
	g->mgr_cutscene.current_cutscene->current =
		g->mgr_cutscene.current_cutscene->animation;
	if (!ft_strcmp(name, VIDEO_BULLET_TIME))
		snd_play_bullet_time(&g->mgr_cutscene);
	else if (!ft_strcmp(name, VIDEO_THE_ONE))
		snd_play_the_one(&g->mgr_cutscene);
}