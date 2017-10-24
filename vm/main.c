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
		if (!add_option(e, argv, &i, argc) && (i < argc))
			add_player(e, argv, &i);
		if (e->num_players > MAX_PLAYERS)
			error_exit(e, 8);
	}
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

void		free_player(void *content, size_t size)
{
	(void)size;
	SAFE_DELETE(((t_player*)content)->name);
	SAFE_DELETE(content);
}

void		free_process(void *content, size_t size)
{
	(void)size;
	SAFE_DELETE(content);
}

void		delete_env(t_env *env)
{
	ft_lstdel(&env->processes, free_process);
	ft_lstdel(&env->players, free_player);
	SAFE_DELETE(env->new_player);
	SAFE_DELETE(env->new_process);
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
	board = create_board();
	env = create_env(board);
	parse_flags(env, argc, argv);
	run_game(env);
	declare_winner(env);
	ft_printf("cycle_to_die %d\n", env->cycle_to_die);
	ft_printf("total cycles %d\n", env->total_cycles);
	delete_env(env);
	return (0);
}
