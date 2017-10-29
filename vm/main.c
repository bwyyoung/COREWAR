/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/29 17:35:10 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

t_bool		add_option(t_env *e, char **argv, int *i, int argc)
{
	if (ft_strequ(argv[*i], "-d"))
		return (get_dump_number(e, argv[*i + 1], i, argc));
	else if (ft_strequ(argv[*i], "-s"))
		return (get_cycle_number(e, argv[*i + 1], i, argc));
	else if (ft_strequ(argv[*i], "--visual"))
		return (add_visual(e));
	else if (ft_strequ(argv[*i], "-v"))
		return (get_verbose_level(e, argv[*i + 1], i, argc));
	else if (ft_strequ(argv[*i], "-b"))
		return (add_binary(e));
	else if (ft_strequ(argv[*i], "--stealth"))
		return (add_stealth(e));
	return (t_false);
}

int				count_players(t_env *env, t_player *player)
{
	int num_players;

	num_players = 0;
	while (player)
	{
		num_players++;
		player = player->next;
	}
	if (num_players == 0)
	{
		print_instructions();
		exit(1);
	}
	else if (num_players > MAX_PLAYERS)
		error_exit(env, 8);
	return (num_players);
}

void			parse_flags(t_env *e, int argc, char **argv)
{
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (!add_option(e, argv, &i, argc) && (i < argc))
			add_player(e, argv, &i);
	}
	e->num_players = count_players(e, e->lst_players);
	load_players(e);
}

/*
** Declare the winner of the game.
** If no player has gotten a live then the player who was added last wins.
** So if there are four player player 4 will win.
** Else the player who has gotten the last live wins
*/
void	declare_winner(t_env *env)
{
	if (!env->last_live_name)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		env->lst_players->prog_num * -1, env->lst_players->name);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		env->last_live_num * -1,
		env->last_live_name);
}

void		delete_env(t_env *env)
{
	lst_process_clr(env);
	lst_players_clr(env);
	SAFE_DELETE(env->board);
	SAFE_DELETE(env);
}

int			main(int argc, char *argv[])
{
	uint8_t			*board;
	t_env			*env;

	if (argc < 2)
	{
		print_instructions();
		return (0);
	}
	srand(time(NULL));
	board = create_board();
	env = create_env(board);
	parse_flags(env, argc, argv);
	if (env->options[visual])
		graphics_loop(env);
	else
	{
		run_game(env);
		declare_winner(env);
	}
	delete_env(env);
	return (0);
}
