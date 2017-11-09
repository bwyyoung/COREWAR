/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_board.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void		ft_hex(int dec, char *buffer)
{
	int		quotient;
	int		rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quotient = dec;
	if (dec > 255 || dec < 0 || !buffer)
		return ;
	ft_memset((void *)buffer, 48, sizeof(char) * 2);
	while (quotient != 0)
	{
		rest = quotient % 16;
		if (rest < 10)
			buffer[j++] = 48 + rest;
		else
			buffer[j++] = 55 + 32 + rest;
		quotient = quotient / 16;
	}
	buffer = ft_strrev(buffer);
}

void		render_cell(t_graphics *g, t_env *e)
{
	render_player(g, e->prog_num_board[g->window_index]);
	mvwprintw(g->game_window, g->window_y,
		g->window_x * 2 + g->window_x, "%02X", e->board[g->window_index]);
}

void		render_board(t_graphics *g, t_env *e)
{
	g->window_x = 0;
	g->window_y = 0;
	g->window_index = -1;
	while (g->window_index++ < MEM_SIZE)
	{
		if (g->window_x >= BOARD_WIDTH)
		{
			g->window_x = 0;
			g->window_y++;
		}
		if (g->window_y < BOARD_HEIGHT)
			render_cell(g, e);
		g->window_x++;
	}
}
