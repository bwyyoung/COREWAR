/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_gameover.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			game_over(t_graphics *g, t_env *e)
{
	if (!g->game_over || (g->init_game_over_menu))
		return ;
	if (ENABLE_SOUND)
		snd_delete_playing_audio(&g->mgr_cutscene);
	declare_winner(e);
	wnoutrefresh(g->log_window);
	doupdate();
	g->neo_wins = false;
	if (e->last_live_num == e->lst_players->prog_num)
		if (!ft_strcmp(e->last_live_name, e->lst_players->name))
			g->neo_wins = true;
	if (g->neo_wins)
		play_cutscene(g, VIDEO_THE_ONE);
	else
		play_cutscene(g, VIDEO_BULLET_TIME);
	g->init_game_over_menu = true;
	if (ENABLE_SOUND)
		snd_play_beep(&g->mgr_cutscene);
}

void			prep_game_over(t_graphics *g)
{
	g->mgr_cutscene.is_scene_playing = false;
	wnoutrefresh(g->video_window);
	if (!g->game_over || !g->init_game_over_menu)
		return;
	if (g->neo_wins)
		prep_cutscene(g, VIDEO_NEO_WINS);
	else
		prep_cutscene(g, VIDEO_NEO_LOSE);
	g->mgr_cutscene.pill = g->mgr_cutscene.cutscenes;
	while (g->mgr_cutscene.pill)
	{
		if (!ft_strcmp(VIDEO_PILL, g->mgr_cutscene.pill->video_file))
			break ;
		g->mgr_cutscene.pill = g->mgr_cutscene.pill->next;
	}
	g->mgr_cutscene.pill->current = g->mgr_cutscene.pill->animation;
	if (!ENABLE_SOUND)
		return ;
	snd_delete_playing_audio(&g->mgr_cutscene);
	play_audio(&g->mgr_cutscene, start,
		g->mgr_cutscene.current_cutscene->sound_file, false);
}
