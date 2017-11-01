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

void				init_cutscenes(t_mgr_scene *scene)
{
	scene->binary_path = getcwd(NULL, 4096);
	snd_init_audio(scene);
}

void				destroy_cutscenes(t_mgr_scene *scene)
{
	if (!Pa_IsStreamStopped(scene->stream))
		Pa_StopStream(scene->stream);
	snd_delete_playing_audio(scene);
	snd_destroy_audio(scene);
	SAFE_DELETE(scene->binary_path);
}
