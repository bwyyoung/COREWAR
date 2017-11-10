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
	wattron(g->game_window, COLOR_PAIR(GREEN_PAIR));
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
	wattroff(g->game_window, COLOR_PAIR(GREEN_PAIR));
}

void					render_stats(t_graphics *g, t_env *e)
{
	render_logo(g);
	wattron(g->game_window, COLOR_PAIR(CYAN_PAIR));
	mvwprintw(g->game_window, 8, 229, "Cycle       : ");
	mvwprintw(g->game_window, 8, 243, "%ld", e->total_cycles);
	mvwprintw(g->game_window, 9, 229, "Processes   : ");
	mvwprintw(g->game_window, 9, 243, "%lu", e->num_processes);
	mvwprintw(g->game_window, 10, 229, "Players     : ");
	mvwprintw(g->game_window, 10, 243, "%i", e->num_players);
	mvwprintw(g->game_window, 11, 229, "Cycle_To_Die: ");
	mvwprintw(g->game_window, 11, 243, "%i", e->cycle_to_die);
	mvwprintw(g->game_window, 12, 229, "Cycle_Delta : ");
	mvwprintw(g->game_window, 12, 243, "%i", CYCLE_DELTA);
	mvwprintw(g->game_window, 13, 229, "Nbr_Live    : ");
	mvwprintw(g->game_window, 13, 243, "%i", NBR_LIVE);
	mvwprintw(g->game_window, 14, 229, "Max_Checks  : ");
	mvwprintw(g->game_window, 14, 243, "%i", MAX_CHECKS);
	wattroff(g->game_window, COLOR_PAIR(CYAN_PAIR));
}
