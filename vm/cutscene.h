/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>            +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/23 21:48:45 by byoung-w          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUTSCENE_H
# define CUTSCENE_H
# define SCENE_FRAME_HEIGHT 58
# include "sound/sndfile.h"
# include "sound/portaudio.h"

typedef struct				s_audiofile
{
	SNDFILE					*data;
	SF_INFO					info;
}							t_audiofile;

typedef struct				s_playback
{
	t_audiofile				*audioFile;
	int						position;
	bool					loop;
}							t_playback;

enum audioeventtype
{
	start,
	stop
};

typedef struct				s_scene_frame
{
	char					**frame;
	struct s_scene_frame	*prev;
	struct s_scene_frame	*next;
}							t_scene_frame;

typedef struct				s_cutscene
{
	t_scene_frame			*animation;
	char					*audio_file;
	char					*video_file;
	t_playback				audio_data;
}							t_cutscene;

t_scene_frame				*load_cutscene_video(char *file);
void						load_cutscene_audio(t_cutscene *scene, char *file);

void 						snd_processevent(enum audioeventtype t,
							t_audiofile *af,
							bool loop);
int							snd_portaudiocallback(const void * input,
							void * output,
							unsigned long framecount,
							const PaStreamCallbackTimeInfo * patimeinfo,
							PaStreamCallbackFlags statusflags,
							void * userdata);
void						snd_init_audio(void);

#endif
