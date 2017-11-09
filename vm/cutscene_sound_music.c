/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_sound_music.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cost <mda-cost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:28:34 by mda-cost          #+#    #+#             */
/*   Updated: 2017/11/09 20:28:36 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void					snd_play_background_music(t_mgr_scene *snd)
{
	if (ENABLE_SOUND)
		play_audio(snd, start, SOUND_BACKGROUND, true);
}

void					snd_play_beep(t_mgr_scene *snd)
{
	if (ENABLE_SOUND)
		play_audio(snd, start, SOUND_BEEP, false);
}

void					snd_play_bullet_time(t_mgr_scene *snd)
{
	if (ENABLE_SOUND)
		play_audio(snd, start, SOUND_BULLET_TIME, false);
}

void					snd_play_the_one(t_mgr_scene *snd)
{
	if (ENABLE_SOUND)
		play_audio(snd, start, SOUND_THE_ONE, false);
}
