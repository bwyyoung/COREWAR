/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/03 09:50:50 by byoung-w          #+#    #+#             */
/*   Updated: 2015/04/29 16:15:25 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static void		ft_llist_push_front(t_llist **begin_list, void *data, int fd)
{
	t_llist		*mlist;

	if (!(mlist = (t_llist *)malloc(sizeof(t_llist))))
		return ;
	mlist->next = NULL;
	mlist->data = data;
	mlist->spill = NULL;
	mlist->fd = fd;
	if (*begin_list == NULL)
		*begin_list = mlist;
	else
	{
		mlist->next = *begin_list;
		*begin_list = mlist;
	}
}

t_llist			*ft_llist_find(t_llist **begin_list, int fd, char **buffer)
{
	t_llist		*list_ptr;

	list_ptr = *begin_list;
	if (!(*buffer = (char *)ft_memalloc(BUFF_SIZE + 1)))
		return (NULL);
	if (*begin_list == NULL)
	{
		ft_llist_push_front(begin_list, NULL, fd);
		return (*begin_list);
	}
	while (list_ptr->next != NULL)
	{
		if (list_ptr->fd == fd)
			return (list_ptr);
		list_ptr = list_ptr->next;
	}
	if (list_ptr->fd == fd)
		return (list_ptr);
	ft_llist_push_front(begin_list, NULL, fd);
	return (*begin_list);
}

static int		processnewline(char *temp, t_llist **curlist)
{
	int		len;
	char	*sub;

	len = temp - (*curlist)->data;
	sub = ft_strsub((*curlist)->data, len + 1,
	ft_strlen((*curlist)->data) - len + 1);
	if (!((*curlist)->spill = sub))
		return (-1);
	if (!(temp = ft_strsub((*curlist)->data, 0, len)))
		return (-1);
	free((*curlist)->data);
	(*curlist)->data = temp;
	return (1);
}

static int		findnewline(char *buffer, t_llist **curlist, int res)
{
	char	*temp;

	if ((*curlist)->spill != NULL)
	{
		(*curlist)->data = ft_strdup((*curlist)->spill);
		free((*curlist)->spill);
		(*curlist)->spill = NULL;
	}
	if (buffer != NULL)
	{
		buffer[res] = '\0';
		if ((*curlist)->data != NULL)
		{
			if (!(temp = ft_strjoin((*curlist)->data, buffer)))
				return (-1);
			free((*curlist)->data);
			(*curlist)->data = temp;
		}
		else
			(*curlist)->data = ft_strdup(buffer);
	}
	if ((temp = ft_strchr((const char *)(*curlist)->data, NEWLINE)))
		return (processnewline(temp, curlist));
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static t_llist		*mylist = NULL;
	t_llist				*clist;
	char				*buff;
	int					res;

	clist = ft_llist_find(&mylist, fd, &buff);
	if (!line || (clist == NULL))
		return (-1);
	*line = NULL;
	while ((((res = read(fd, buff, BUFF_SIZE)) > 0)) || (clist->spill != NULL))
	{
		if (res == -1 || ((res == 0 && !ft_strlen(clist->spill))))
		{
			SAFE_DELETE_GNL(-1, buff);
		}
		res = findnewline(buff, &clist, res);
		*line = clist->data;
		if (res != 1 && res != -1)
			continue ;
		SAFE_DELETE_GNL(res, buff);
	}
	if (*line == NULL)
		*line = ft_memalloc(1);
	SAFE_DELETE_GNL(res, buff);
}
