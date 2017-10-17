/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:28:19 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/15 13:28:30 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_malloc_new(char **buf, int size)
{
	int		i;
	char	*tmp;

	tmp = *buf;
	*buf = malloc(sizeof(char) * (ft_strlen(tmp) + size + 1));
	i = -1;
	while (tmp[++i] != '\0')
		(*buf)[i] = tmp[i];
	(*buf)[i] = '\0';
	free(tmp);
	return (i);
}

static int		get_part(char **buf, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *buf;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] != '\n')
		return (0);
	tmp[i] = '\0';
	*line = ft_strdup(*buf);
	*buf = ft_strdup(*buf + i + 1);
	free(tmp);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static char		*buf = NULL;
	int				ret;
	int				i;
	static int		real = 1;

	if (!real)
		return (0);
	if (buf == NULL)
		buf = ft_strdup("");
	if (get_part(&buf, line))
		return (1);
	i = ft_malloc_new(&buf, BUF_SIZE);
	ret = read(fd, buf + i, BUF_SIZE);
	if (ret == -1)
		return (-1);
	buf[i + ret] = '\0';
	if (ret != 0)
		return (get_next_line(fd, line));
	*line = ft_strdup(buf);
	free(buf);
	return (real--);
}
