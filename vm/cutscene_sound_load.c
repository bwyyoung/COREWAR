/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_sound_load.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:33:54 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/09 20:33:57 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

t_audiofile					*audio_exists(t_mgr_scene *snd, char *thefile)
{
	snd->current_audiofile = snd->audiofiles;
	while (snd->current_audiofile)
	{
		if (!ft_strcmp(snd->current_audiofile->file_name, thefile))
			return (snd->current_audiofile);
		snd->current_audiofile = snd->current_audiofile->next;
	}
	return (NULL);
}

t_audiofile					*create_audiofile(t_mgr_scene *snd, char *thefile)
{
	SF_INFO		info;

	snd->new_audiofile = (t_audiofile *)malloc(sizeof(t_audiofile));
	snd->new_audiofile->file_name = ft_strdup(thefile);
	snd->new_audiofile->full_path = ft_strjoin(snd->binary_path,
		snd->new_audiofile->file_name);
	snd->new_audiofile->next = NULL;
	info.format = 0;
	snd->new_audiofile->data = sf_open(snd->new_audiofile->full_path,
		SFM_READ, &info);
	if (!(snd->new_audiofile->data))
		ft_error_errno("Audio File Error Loading\n");
	ft_memcpy(&snd->new_audiofile->info, &info, sizeof(SF_INFO));
	if (!snd->new_audiofile->data)
		ft_error_errno(NULL);
	snd->current_audiofile = snd->audiofiles;
	if (!snd->audiofiles)
	{
		snd->audiofiles = snd->new_audiofile;
		return (snd->audiofiles);
	}
	while (snd->current_audiofile->next)
		snd->current_audiofile = snd->current_audiofile->next;
	snd->current_audiofile->next = snd->new_audiofile;
	return (snd->new_audiofile);
}

t_audio						*new_audio(t_mgr_scene *snd, char *thefile,
bool loop)
{
	t_audio		*a;
	t_audiofile	*b;

	a = (t_audio *)malloc(sizeof(t_audio));
	if (!a)
		ft_error_errno(NULL);
	if (!(b = audio_exists(snd, thefile)))
		b = create_audiofile(snd, thefile);
	a->pb = (t_playback *)malloc(sizeof(t_playback));
	a->pb->pos = 0;
	a->next = NULL;
	a->prev = NULL;
	a->pb->af = b;
	a->pb->loop = loop;
	return (a);
}

int							play_audio(t_mgr_scene *snd,
							enum audioeventtype type,
							char *thefile, bool loop)
{
	if (type == start)
	{
		if (Pa_IsStreamStopped(snd->stream))
			Pa_StartStream(snd->stream);
		if (!snd->sounds)
			return ((snd->sounds = new_audio(snd, thefile, loop)) != NULL);
		snd->new_s = snd->sounds;
		while (snd->new_s->next != NULL)
			snd->new_s = snd->new_s->next;
		snd->new_s->next = new_audio(snd, thefile, loop);
		snd->new_s->next->prev = snd->new_s;
	}
	else if (type == stop)
	{
		snd_delete_playing_audio(snd);
	}
	return (0);
}
