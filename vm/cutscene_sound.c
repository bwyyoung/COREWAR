/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_sound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:30:16 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/09 20:30:20 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void						snd_init_audio(t_mgr_scene *snd)
{
	snd->errorcode = Pa_Initialize();
	snd->sounds = NULL;
	snd->s = NULL;
	snd->no_input = NULL;
	snd->cutscenes = NULL;
	snd->sndparameters.device = Pa_GetDefaultOutputDevice();
	snd->sndparameters.channelCount = CHANNEL_COUNT;
	snd->sndparameters.sampleFormat = paInt32;
	snd->sndparameters.suggestedLatency = 1;
	snd->sndparameters.hostApiSpecificStreamInfo = 0;
	snd->streamcallback = portaudiocallback;
	snd->errorcode = Pa_OpenStream(&snd->stream, snd->no_input,
		&snd->sndparameters, SAMPLE_RATE, 2048, paNoFlag, snd->streamcallback,
		snd);
	if (snd->errorcode)
	{
		Pa_Terminate();
		ft_printf("Pa_OpenStream error %i|%s\n", snd->errorcode,
			Pa_GetErrorText(snd->errorcode));
		ft_error_errno(NULL);
	}
}

void						snd_delete_playing_audio(t_mgr_scene *snd)
{
	if (!snd)
		return ;
	if (!Pa_IsStreamStopped(snd->stream))
		Pa_StopStream(snd->stream);
	snd->new_s = snd->sounds;
	while (snd->new_s)
	{
		SAFE_DELETE(snd->new_s->outputbuffer);
		SAFE_DELETE(snd->new_s->pb);
		snd->s = snd->new_s->next;
		SAFE_DELETE(snd->new_s);
		snd->new_s = snd->s;
	}
	snd->sounds = NULL;
}

void						snd_destroy_audio(t_mgr_scene *snd)
{
	if (!snd)
		return ;
	if (!Pa_IsStreamStopped(snd->stream))
		Pa_StopStream(snd->stream);
	snd->current_audiofile = snd->audiofiles;
	while (snd->current_audiofile)
	{
		sf_close(snd->current_audiofile->data);
		SAFE_DELETE(snd->current_audiofile->full_path);
		SAFE_DELETE(snd->current_audiofile->file_name);
		snd->new_audiofile = snd->current_audiofile->next;
		SAFE_DELETE(snd->current_audiofile);
		snd->current_audiofile = snd->new_audiofile;
	}
	Pa_Terminate();
}
