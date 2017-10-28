/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics_stats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mgr_graphics.h"
#include "vm.h"

void					render_logo(t_graphics *g)
{

	mvwaddstr(g->game_window, 0, 191, "▄███████ ▄█████▄ ▄██████ ▄███████▄█     "
		" █▄  ▄███████   ▄██████");
	mvwaddstr(g->game_window, 1, 191, "███   █████   ██  ██   ██ ██   █████    "
		" ██  ██    ██  ██    ██");
	mvwaddstr(g->game_window, 2, 191, "███   █▀ ██   ██  ██   ██ ██   █▀ ██    "
		" ██  ██    ██  ██    ██");
	mvwaddstr(g->game_window, 3, 191, "███      ██   ██ ▄██▄▄▄█▀ ██▄▄    ██    "
		" ██  ██    ██ ▄██▄▄▄▄█▀");
	mvwaddstr(g->game_window, 4, 191, "███      ██   ██▀▀██▀▀▀▀█ ██▀▀    ██  █ "
		" ██▀█████████▀▀██▀▀▀▀▀");
	mvwaddstr(g->game_window, 5, 191, "███   █▄ ██   ██▀████████ ██   █▄ ██  █ "
		" ██  ██    ██▀█████████");
	mvwaddstr(g->game_window, 6, 191, "███   █████   ██  ██   ██ ██   █████ ▄█▄"
		" ██  ██    ██  ██    ██");
	mvwaddstr(g->game_window, 7, 191, "███████▀  ▀████▀  ██   ██ ████████▀███▀█"
		"██▀  ██    █▀  ██    ██");
};

void					write_stats(WINDOW *g, int y, int x, char *str)
{
	mvwprintw(g, y, x, str);
	SAFE_DELETE(str);
}

void					render_stats(t_graphics *g, t_env *e)
{
	render_logo(g);
	mvwprintw(g->game_window, 8, 199, "Cycle       : ");
	write_stats(g->game_window, 8, 215, ft_itoa(e->total_cycles));
	mvwprintw(g->game_window, 10, 199, "Processes   : ");
	write_stats(g->game_window, 10, 215, ft_itoa(e->num_processes));
	mvwprintw(g->game_window, 12, 199, "Players     : ");
	write_stats(g->game_window, 12, 215, ft_itoa(e->num_players));
	mvwprintw(g->game_window, 14, 199, "Cycle_To_Die: ");
	write_stats(g->game_window, 14, 215, ft_itoa(e->cycle_to_die));
	mvwprintw(g->game_window, 16, 199, "Cycle_Delta : ");
	write_stats(g->game_window, 16, 215, ft_itoa(CYCLE_DELTA));
	mvwprintw(g->game_window, 18, 199, "Nbr_Live    : ");
	mvwprintw(g->game_window, 18, 215, "Unknown");
	mvwprintw(g->game_window, 20, 199, "Max_Checks  : ");
	write_stats(g->game_window, 20, 215, ft_itoa(MAX_CHECKS));
}
