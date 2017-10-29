/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "matrix.h"
#include "mgr_graphics.h"

void		init_matrix(WINDOW **mainwin, struct s_matrix **mat)
{
	*mat = malloc(sizeof(struct s_matrix));
	*mainwin = newwin(0, 0, 0, 0);
	(*mat)->cols = malloc(sizeof(struct s_column) * COLS/ 2);
	(*mat)->c = COLS;
	(*mat)->r = LINES;
	start_color();
	init_pair(WHITE_PAIR, COLOR_WHITE, COLOR_BLACK);
	init_pair(GREEN_PAIR, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW_PAIR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(RED_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(MAGENTA_PAIR, COLOR_MAGENTA, COLOR_BLACK);
	wbkgd(*mainwin, COLOR_PAIR(1));
	ft_memset((*mat)->cols, 0, sizeof(struct s_column) * (*mat)->c / 2);
	(*mat)->i = -1;
	while (++(*mat)->i < (*mat)->c / 2)
	{
		((*mat)->cols[(*mat)->i]).rows =
			(char *) malloc((*mat)->r * sizeof(char));
		ft_bzero((void *)((*mat)->cols[(*mat)->i]).rows,
		(*mat)->r * sizeof(char));
	}
}

char		matrix_char(void)
{
	char		*mat;

	mat = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
		"abcdefghijklmnopqrstuvwxyz{|}~";
	return (mat[RANDOM_NUM(ft_strlen(mat))]);
}

void		loop_matrix_sub(t_graphics *g, struct s_column *col,
WINDOW *mainwin, int *flag)
{
	g->mat->j = g->mat->r;
	while (--g->mat->j  >= 0)
	{
		if (g->mat->j > g->offsety && g->mat->j < (g->offsety + WORLD_HEIGHT))
			if ((g->mat->i * 2) > g->offsetx && (g->mat->i * 2) <
			(g->offsetx + WORLD_WIDTH))
				continue ;
		if (col->rows[g->mat->j] != '\0')
		{
			if (PROB(10))
				col->rows[g->mat->j] = matrix_char();
			if (*flag && PROB(40))
				col->rows[g->mat->j] = matrix_char();
			mvwaddch(mainwin, g->mat->j, g->mat->i * 2, col->rows[g->mat->j]);
			if (*flag == 0)
				continue ;
			*flag = 0;
			wattroff(mainwin, COLOR_PAIR(WHITE_PAIR));
			wattron(mainwin, COLOR_PAIR(GREEN_PAIR));
			continue ;
		}
		*flag = 1;
		wattroff(mainwin, COLOR_PAIR(GREEN_PAIR));
		wattron(mainwin, COLOR_PAIR(WHITE_PAIR));
	}
}

void		loop_matrix(t_graphics *g, WINDOW *mainwin, int flag,
struct s_column *col)
{
	g->mat->i = -1;
	while (++g->mat->i < g->mat->c / 2)
	{
		col = &g->mat->cols[g->mat->i];
		ft_memmove(col->rows + 1, col->rows, g->mat->r - 1);
		g->mat->j = g->mat->r;
		if(!(col->rows[1]))
		{
			if (PROB(5))
				col->rows[0] = matrix_char();
		}
		else if (PROB(20))
				col->rows[0] = 0;
		else
			col->rows[0] = matrix_char();
		flag = 0;
		wattron(mainwin, COLOR_PAIR(GREEN_PAIR));
		loop_matrix_sub(g, col, mainwin, &flag);
	}
};
