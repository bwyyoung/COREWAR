/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 16:56:06 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/24 16:56:09 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_buf_compress(char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!buf[i])
		return (0);
	while (buf[j] && buf[j] != '\n')
		j++;
	if (buf[j])
		j++;
	while (buf[j])
		buf[i++] = buf[j++];
	buf[i] = '\0';
	return (1);
}

static char	*ft_buf_read(char *str, char *buf)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (str)
		len = ft_strlen(str);
	if (!(new = (char *)malloc(sizeof(char) * (len + ft_strlen(buf) + 1))))
		return (NULL);
	while (str && str[i])
	{
		new[i] = str[i];
		if (str[i++] == '\n')
		{
			new[i - 1] = '\0';
			free(str);
			return (new);
		}
	}
	while (buf && *buf && *buf != '\n')
		new[i++] = *buf++;
	new[i] = '\0';
	free(str);
	return (new);
}

int			get_next_line(int const fd, char **line)
{
	int				ret;
	char			*str;
	static char		buf[5][BUFF_SIZE + 1];

	str = NULL;
	if (fd < 0 || fd > 5 || BUFF_SIZE < 1 || line == NULL)
		return (-1);
	if (!(str = ft_strdup(buf[fd])))
		return (-1);
	if (!ft_strstr(str, "\n"))
		while ((ret = read(fd, buf[fd], BUFF_SIZE)))
		{
			if (ret == -1)
				return (-1);
			buf[fd][ret] = '\0';
			if (!(str = ft_buf_read(str, buf[fd])))
				return (-1);
			if (ft_strstr(buf[fd], "\n"))
				break ;
		}
	else if (!(str = ft_buf_read(str, buf[fd])))
		return (-1);
	*line = str;
	return (ft_buf_compress(buf[fd]));
}
