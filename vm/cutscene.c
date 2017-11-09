/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cost <mda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:16:14 by mda-cost          #+#    #+#             */
/*   Updated: 2017/11/09 20:16:55 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void				load_cutscene(t_mgr_scene *g, char *s, char *a, int f)
{
	g->new_cutscene = (t_cutscene *)malloc(sizeof(t_cutscene));
	g->new_cutscene->video_file = ft_strdup(s);
	g->new_cutscene->full_path = ft_strjoin(g->binary_path,
	g->new_cutscene->video_file);
	g->new_cutscene->index = 0;
	g->new_cutscene->animation = NULL;
	g->new_cutscene->refresh_rate = f;
	load_cutscene_video(g->new_cutscene);
	g->new_cutscene->next = NULL;
	g->new_cutscene->sound_file = ft_strdup(a);
	g->current_cutscene = g->cutscenes;
	if (!g->cutscenes)
	{
		g->cutscenes = g->new_cutscene;
		return ;
	}
	while (g->current_cutscene->next)
		g->current_cutscene = g->current_cutscene->next;
	g->current_cutscene->next = g->new_cutscene;
}

void				init_cutscenes(t_mgr_scene *scene)
{
	scene->binary_path = getcwd(NULL, 4096);
	if (ENABLE_SOUND)
		snd_init_audio(scene);
	scene->cutscenes = NULL;
	load_cutscene(scene, VIDEO_BULLET_TIME, SOUND_BULLET_TIME, 80);
	load_cutscene(scene, VIDEO_THE_ONE, SOUND_THE_ONE, 90);
	load_cutscene(scene, VIDEO_NEO_WINS, SOUND_GAMEOVER, 0);
	load_cutscene(scene, VIDEO_NEO_LOSE, SOUND_GAMEOVER, 0);
	load_cutscene(scene, VIDEO_PILL, SOUND_GAMEOVER, 0);
	scene->dialog_intro = load_dialog(scene, DIALOG_INTRO_VID, DIALOG_INTRO_SND,
	DIALOG_INTRO_SUB);
	scene->dialog_intro->finished = &snd_play_background_music;
	scene->is_dialog_playing = false;
	scene->is_scene_playing = false;
}

void				destroy_animation(t_mgr_scene *scene)
{
	CURSCENE->index = -1;
	while (++CURSCENE->index < CUTSCENE_HEIGHT)
	{
		SAFE_DELETE(CURSCENE->animation->frame[CURSCENE->index]);
	}
	SAFE_DELETE(CURSCENE->animation->frame);
	SAFE_DELETE(CURSCENE->full_path);
	SAFE_DELETE(CURSCENE->video_file);
	SAFE_DELETE(CURSCENE->sound_file);
	CURSCENE->prev = CURSCENE->animation;
	CURSCENE->animation = CURSCENE->animation->next;
	SAFE_DELETE(CURSCENE->prev);
}

void				destroy_cutscenes(t_mgr_scene *scene)
{
	if (ENABLE_SOUND)
	{
		snd_delete_playing_audio(scene);
		snd_destroy_audio(scene);
	}
	SAFE_DELETE(scene->binary_path);
	CURSCENE = scene->cutscenes;
	while (CURSCENE)
	{
		while (CURSCENE->animation)
			destroy_animation(scene);
		scene->new_cutscene = CURSCENE->next;
		SAFE_DELETE(CURSCENE);
		CURSCENE = scene->new_cutscene;
	}
	delete_dialog(scene->dialog_intro);
}
