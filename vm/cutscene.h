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
# define CUTSCENE_WIDTH 200
# define CUTSCENE_HEIGHT 60
# define SAMPLE_RATE 44100
# define CHANNEL_COUNT 2
# include "sound/sndfile.h"
# include "sound/portaudio.h"
# define ENABLE_SOUND true
# define SOUND_BACKGROUND "/sound/burly_brawl2.ogg"
# define SOUND_BULLET_TIME "/sound/bullet_time.ogg"
# define SOUND_THE_ONE "/sound/the_one.ogg"
# define SOUND_BEEP "/sound/Powerup14.wav"
# define VIDEO_BULLET_TIME "/animation/bullet_time.txt"
# define VIDEO_THE_ONE "/animation/the_one.txt"
# define DIALOG_INTRO_VID "/animation/intro.txt"
# define DIALOG_INTRO_SUB "/animation/script_intro.txt"
# define DIALOG_INTRO_SND "/sound/intro_speech.ogg"
# define AVATAR_NEO "(⌐■_■)_•︻̷┻̿═━一"
# define AVATAR_SMITH "╾━╤デ╦︻(▀̿̿Ĺ̯̿̿▀̿ ̿)"
# define CURSCENE scene->current_cutscene
# define G ((t_mgr_scene *)userdata)
# ifdef WIN32
#  else
typedef long					dword;
typedef unsigned long			uword;
typedef unsigned short			word;
typedef unsigned int			unint32;
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
	uword					i;
	unint32					framesleft;
	unint32					framesread;
	int						*buffercursor;
	int						*outputcursor;
	int 					*outputbuffer;
	bool					playbackended;
	uword					stereoframecount;
}
							t_audio;

typedef struct				s_scene_frame
{
	char					**frame;
	struct s_scene_frame	*next;
}							t_scene_frame;

typedef struct				s_cutscene
{
	t_scene_frame			*animation;
	t_scene_frame			*current;
	t_scene_frame			*prev;
	char					*video_file;
	char					*full_path;
	struct s_cutscene		*next;
	int						pfd;
	int						index;
	int						status;
	char					*sound_file;
	int						refresh_rate;
	char					*line;
}							t_cutscene;

typedef struct				s_subtitle
{
	struct s_subtitle		*prev;
	struct s_subtitle		*next;
	char					*text;
	int						timestamp;
}							t_subtitle;

typedef struct 				s_mgr_scene t_mgr_scene;
typedef struct				s_dialog
{
	bool					is_playing;
	t_subtitle				*subtitle;
	t_subtitle				*current;
	t_subtitle				*prev;
	int						pfd;
	char					*video_file;
	char					*sound_file;
	char 					*sub_file;
	char 					*full_sub_path;
	char					*line;
	int						status;
	int						duration;
	void 					(*finished)(t_mgr_scene *);
}							t_dialog;

typedef struct 				s_mgr_scene
{
	t_cutscene				*cutscenes;
	t_cutscene				*new_cutscene;
	t_cutscene				*current_cutscene;
	t_dialog				*dialog_intro;
	t_dialog				*current_dialog;
	bool					skip_intro;
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
	uword					stereoframecount;
	bool					is_scene_playing;
	bool					is_dialog_playing;
}							t_mgr_scene;

void						load_cutscene(t_mgr_scene *g, char *s, char *a,
							int f);
void						load_cutscene_video(t_cutscene *s);
void 						snd_processevent(enum audioeventtype t,
							t_audiofile *af,
							bool loop);
t_dialog					*load_dialog(t_mgr_scene *g, char *video,
	char *audio, char *sub);
void						delete_dialog(t_dialog *d);
void						play_dialog(t_graphics *g, t_dialog *d);
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
void						prep_cutscene(t_graphics *g, char *name);
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
void 						snd_play_bullet_time(t_mgr_scene *snd);
void 						snd_play_the_one(t_mgr_scene *snd);
void						render_cutscene(t_graphics *g);
void						render_dialog(t_graphics *g);
#endif
