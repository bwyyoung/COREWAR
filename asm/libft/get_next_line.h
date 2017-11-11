/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/11/11 22:07:51 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# define BUFF_SIZE 1000000
# define NEWLINE 10
# define SAFE_DELETE_GNL(b, a) if((a) != NULL){free(a); (a) = NULL;} return (b);

typedef struct		s_llist
{
	char			*data;
	char			*spill;
	int				fd;
	struct s_llist	*next;
}					t_llist;
int					get_next_line(int const fd, char **line);

#endif
