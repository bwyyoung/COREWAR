/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bool			add_option(t_env *e, char **argv, int *i, int argc)
{
	if (ft_strequ(argv[*i], "-d"))
	{
		e->options[d] = true;
		get_dump_number(e, argv[*i + 1], i,argc);
		*i += 1;
	}
	else if (ft_strequ(argv[*i], "-s"))
		e->options[s] = true;
	else if (ft_strequ(argv[*i], "--visual"))
	{
		e->options[visual] = 1;
		add_bonus(e, argc, i);
	}
	else if (ft_strequ(argv[*i], "-v"))
		e->options[v] = true;
	else if (ft_strequ(argv[*i], "-b"))
		e->options[b] = true;
	else if (ft_strequ(argv[*i], "--stealth"))
		e->options[stealth] = 1;
}

void			parse_flags(t_env *e, int argc, char **argv)
{
	int	i;

	i = 1;
	e->num_players = 0;
	while (i < argc)
	{
		add_option(e, argv, &i, argc);
		//add_player_empty(e, &i, e->num_players);
		e->num_players += 1;
		if (e->num_players > MAX_PLAYERS)
			error_exit(e, 8);
		i++;
	}
	e->cursors = e->num_players;
}

static void		handle_args(t_env *env, int argc, char *argv[])
{
	int i;

	i = 0;
	while (argv[i + 1])
	{
		if (argv[i][0] == '-')
		{
			//add_option(env, argv[i]);
			env->option_num = ft_atoi(argv[i + 1]);
			argc -= 2;
		}
		i++;
	}
	env->num_players = argc - 1;
}

/*
** Declare the winner of the game.
** If no player has gotten a live then the player who was added last wins.
** So if there are four player player 4 will win.
** Else the player who has gotten the last live wins
*/
static void	declare_winner(t_env *env)
{
	if (!env->last_live_name)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		((t_player*)env->players->content)->prog_num * -1,
		((t_player*)env->players->content)->name);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		env->last_live_num * -1,
		env->last_live_name);
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
	board = create_board();
	env = create_env(board);
	// parse_flags(env, argc, argv);
	handle_args(env, argc, argv);
	load_programs(env, ++argv);
	run_game(env);
	declare_winner(env);
	ft_printf("cycle_to_die %d\n", env->cycle_to_die);
	ft_printf("total cycles %d\n", env->total_cycles);
	SAFE_DELETE(board);
	return (0);
}
