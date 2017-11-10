/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "libft/libft.h"
# include <wchar.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <sys/ioctl.h>
# define RANDOM_NUM(X) ((rand() % (X)))
# define PROB(x) (((rand() % 100) < (x)) ? 1 : 0)

typedef struct s_graphics	t_graphics;

struct					s_column
{
	char				*rows;
};

typedef struct			s_matrix
{
	int					r;
	int					c;
	int					i;
	int					j;
	struct s_column		*cols;
}						t_matrix;

void					init_matrix(WINDOW **mainwin, struct s_matrix **mat);
void					loop_matrix(t_graphics *g, WINDOW *mainwin, int flag,
						struct s_column *col);
#endif
