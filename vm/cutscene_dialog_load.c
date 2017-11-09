/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutscene_dialog_load.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:23:39 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/09 20:23:40 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"

void				break_subtitle(t_dialog *s)
{
	if (!s->subtitle)
		s->subtitle = s->current;
	s->prev = s->current;
	s->current->next = (t_subtitle *)malloc(sizeof(t_subtitle));
	if (!s->current->next)
		ft_error_errno("failed to malloc subtitle\n");
	s->current = s->current->next;
	s->current->next = NULL;
	s->current->prev = s->prev;
	s->current->timestamp = ft_atoi(s->line);
	SAFE_DELETE(s->line);
}

void				load_subtitle(t_dialog *d)
{
	d->pfd = open(d->full_sub_path, O_RDONLY);
	while ((d->status = get_next_line(d->pfd, &d->line)))
	{
		if (ft_strchr(d->line, '>'))
		{
			d->duration = ft_atoi(d->line);
			SAFE_DELETE(d->line);
			continue ;
		}
		if (ft_strchr(d->line, '<'))
		{
			break_subtitle(d);
			continue ;
		}
		d->current->text = d->line;
	}
	SAFE_DELETE(d->line);
	close(d->pfd);
}

t_dialog			*load_dialog(t_mgr_scene *g, char *video, char *audio,
char *sub)
{
	t_dialog		*dialog;

	dialog = (t_dialog *)malloc(sizeof(t_dialog));
	if (!dialog)
		ft_error_errno("Failed to load dialog");
	dialog->subtitle = NULL;
	dialog->sound_file = ft_strdup(audio);
	dialog->video_file = ft_strdup(video);
	dialog->sub_file = ft_strdup(sub);
	dialog->full_sub_path = ft_strjoin(g->binary_path,
		dialog->sub_file);
	dialog->current = (t_subtitle *)malloc(sizeof(t_subtitle));
	if (!dialog->current)
		ft_error_errno("failed to malloc subtitle\n");
	dialog->current->next = NULL;
	dialog->current->prev = NULL;
	dialog->current->timestamp = 0;
	load_subtitle(dialog);
	load_cutscene(g, video, audio, 0);
	return (dialog);
}

void				delete_dialog(t_dialog *d)
{
	SAFE_DELETE(d->sound_file);
	SAFE_DELETE(d->video_file);
	SAFE_DELETE(d->sub_file);
	SAFE_DELETE(d->full_sub_path);
	while (d->subtitle)
	{
		SAFE_DELETE(d->subtitle->text);
		d->current = d->subtitle->next;
		SAFE_DELETE(d->subtitle);
		d->subtitle = d->current;
	}
	SAFE_DELETE(d);
}
