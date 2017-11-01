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
# define SAMPLE_RATE 44100
# define CHANNEL_COUNT 2
# include "sound/sndfile.h"
# include "sound/portaudio.h"
# define ENABLE_SOUND false
# define SOUND_BACKGROUND "/sound/burly_brawl.ogg"
# define SOUND_BEEP "/sound/Powerup14.wav"

# ifdef WIN32
#  else
typedef long					DWORD;
typedef unsigned long			UWORD;
typedef unsigned short			WORD;
typedef unsigned int			UNINT32;
# endif

typedef struct				s_audiofile
{
	struct s_audiofile		*next;
	SNDFILE					*data;
	SF_INFO					info;
	char					*file_name;
	char					*full_path;
}							t_audiofile;

typedef struct				s_playback
{
	t_audiofile				*af;
	sf_count_t				pos;
	bool					loop;
}							t_playback;

enum						audioeventtype
{
							start,
							stop
};

typedef struct				s_audio
{
	struct s_audio			*prev;
	struct s_audio			*next;
	t_playback				*pb;
	SF_INFO					info;
	UWORD					i;
	UNINT32					framesleft;
	UNINT32					framesread;
	int						*buffercursor;
	int						*outputcursor;
	int 					*outputbuffer;
	bool					playbackended;
	UWORD					stereoframecount;
}
							t_audio;

typedef struct				s_scene_frame
{
	char					**frame;
	struct s_scene_frame	*prev;
	struct s_scene_frame	*next;
}							t_scene_frame;

typedef struct				s_cutscene
{
	t_scene_frame			*animation;
	char					*video_file;
	PaError					errorcode;
}							t_cutscene;

typedef struct 				s_mgr_scene
{
	t_cutscene				*cutscenes;
	t_audio					*sounds;
	t_audiofile				*audiofiles;
	t_audiofile				*current_audiofile;
	t_audiofile				*new_audiofile;
	t_audio					*s;
	t_audio					*new_s;
	PaStreamParameters		sndparameters;
	PaStream				*stream;
	char					*binary_path;
	PaError 				errorcode;
	PaStreamParameters		*no_input;
	PaStreamCallback		*streamcallback;
	UWORD					stereoframecount;
}							t_mgr_scene;

t_scene_frame				*load_cutscene_video(char *file);
void						load_cutscene_audio(t_cutscene *scene, char *file);
void 						snd_processevent(enum audioeventtype t,
							t_audiofile *af,
							bool loop);
/*
** Portaudio callback function. It takes 6 parameters, hence
** breaking the norminette, but it is necessary in order to use the library.
**
** http://portaudio.com/docs/v19-doxydocs/
** portaudio_8h.html#a8a60fb2a5ec9cbade3f54a9c978e2710
**
** typedef int PaStreamCallback(const void *input, void *output,
** unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
** PaStreamCallbackFlags statusFlags, void *userData)
*/
int							PortAudioCallback(const void * input,
							void *output,
							unsigned long framecount,
							const PaStreamCallbackTimeInfo * patimeinfo,
							PaStreamCallbackFlags statusflags,
							void *userdata);
void						snd_init_audio(t_mgr_scene *snd);
void						snd_destroy_audio(t_mgr_scene *snd);
void						init_cutscenes(t_mgr_scene *scene);
void						destroy_cutscenes(t_mgr_scene *scene);
int							play_audio(t_mgr_scene *snd,
							enum audioeventtype type,
							char *thefile, bool loop);
void						snd_play_background_music(t_mgr_scene *snd);
void						snd_play_beep(t_mgr_scene *snd);
int							portaudiocallback(const void *input,
								void *output,
								unsigned long frameCount,
								const PaStreamCallbackTimeInfo *paTimeInfo,
								PaStreamCallbackFlags statusFlags,
								void *userData);
void						snd_delete_playing_audio(t_mgr_scene *snd);
#endif
