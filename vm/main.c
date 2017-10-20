/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
	return (false);
}

void			parse_flags(t_env *e, int argc, char **argv)
{
	int	i;

	i = 0;
	e->num_players = 0;
	while (++i < argc)
	{
		ft_printf("parse_flags %i %s\n", i , argv[i]);
		if (!add_option(e, argv, &i, argc) && (i < argc))
			add_player(e, argv, &i);
		if (e->num_players > MAX_PLAYERS)
			error_exit(e, 8);
		ft_printf("parse_flags1 %i/%i %s\n", i , argc, argv[i]);
	}
	ft_printf("Finish Parse Flags\n");
}


void		handle_args(t_env *env, int argc, char *argv[])
{
	int i;

	i = 0;
	while (argv[i + 1])
	{
		if (argv[i][0] == '-')
		{
			//add_option(env, argv[i]);
			env->dump_value = ft_atoi(argv[i + 1]);
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
void	declare_winner(t_env *env)
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
	parse_flags(env, argc, argv);
	//handle_args(env, argc, argv);
	//load_programs(env, ++argv);
	ft_printf("main 1\n");
	run_game(env);
	ft_printf("main 2\n");

	declare_winner(env);
	ft_printf("main 3\n");

	ft_printf("cycle_to_die %d\n", env->cycle_to_die);
	ft_printf("total cycles %d\n", env->total_cycles);
	SAFE_DELETE(board);
	return (0);
}
