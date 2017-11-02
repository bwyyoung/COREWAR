/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/23 21:48:45 by byoung-w          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#define CURSCENE scene->current_cutscene

void				load_cutscene(t_mgr_scene *g, char *s, int framerate)
{
	g->new_cutscene = (t_cutscene *)malloc(sizeof(t_cutscene));
	g->new_cutscene->video_file = ft_strdup(s);
	g->new_cutscene->full_path = ft_strjoin(g->binary_path,
	g->new_cutscene->video_file);
	g->new_cutscene->index = 0;
	g->new_cutscene->animation = NULL;
	g->new_cutscene->refresh_rate = framerate;
	load_cutscene_video(g->new_cutscene);
	g->new_cutscene->next = NULL;
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
	load_cutscene(scene, VIDEO_BULLET_TIME, 80);
	load_cutscene(scene, VIDEO_THE_ONE, 90);
	scene->is_scene_playing = false;
}

void 				destroy_animation(t_mgr_scene *scene)
{
	CURSCENE->index = -1;
	while (++CURSCENE->index < CUTSCENE_HEIGHT)
	{
		SAFE_DELETE(CURSCENE->animation->frame[CURSCENE->index]);
	}
	SAFE_DELETE(CURSCENE->animation->frame);
	SAFE_DELETE(CURSCENE->full_path);
	SAFE_DELETE(CURSCENE->video_file);
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
		while(CURSCENE->animation)
			destroy_animation(scene);
		scene->new_cutscene = CURSCENE->next;
		SAFE_DELETE(CURSCENE);
		CURSCENE = scene->new_cutscene;
	}
}
