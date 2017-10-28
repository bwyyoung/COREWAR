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

#include "matrix.h"

void		init_matrix(WINDOW **mainwin, struct s_matrix **mat)
{
	*mat = malloc(sizeof(struct s_matrix));
	*mainwin = newwin(0, 0, 0, 0);
	(*mat)->cols = malloc(sizeof(struct s_column) * COLS/ 2);

	(*mat)->c = COLS;
	(*mat)->r = LINES;
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
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

void		loop_matrix_sub(struct s_matrix *mat, struct s_column *col,
WINDOW *mainwin, int *flag)
{
	(void)mainwin;
	mat->j = mat->r;

	while (--mat->j  >= 0)
	{
		if (col->rows[mat->j] != '\0')
		{
			if (PROB(10))
				col->rows[mat->j]++;
			if (*flag && PROB(40))
				col->rows[mat->j]++;
			mvwaddch(mainwin, mat->j, mat->i * 2, col->rows[mat->j]);
			if (*flag == 0)
				continue ;
			*flag = 0;
			wattroff(mainwin, COLOR_PAIR(2));
			wattron(mainwin, COLOR_PAIR(1));
			continue ;
		}
		*flag = 1;
		wattroff(mainwin, COLOR_PAIR(1));
		wattron(mainwin, COLOR_PAIR(2));
	}
}

void		loop_matrix(t_matrix *mat, WINDOW *mainwin, int flag,
struct s_column *col)
{
	mat->i = -1;
	while (++mat->i < mat->c / 2)
	{
		col = &mat->cols[mat->i];

		ft_memmove(col->rows + 1, col->rows, mat->r - 1);
		mat->j = mat->r;
		if(!(col->rows[1]))
		{
			if (PROB(7))
				col->rows[0] = RANDOM_NUM;
		}
		else if (PROB(20))
				col->rows[0] = '\0';
		else
			col->rows[0] = RANDOM_NUM;
		flag = 0;
		attron(COLOR_PAIR(2));
		loop_matrix_sub(mat, col, mainwin, &flag);
	}
};
