/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/16 17:50:41 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	parse_flags(t_env *e, int argc, char **argv)
{
	int	i;

	i = 1;
	e->num_players = 0;
	if (ft_strequ(argv[i], "-dump"))
		capture_number(e, argv[i + 1], &i, argc);
	else if (ft_strequ(argv[i], "-visual"))
		add_bonus(e, argc, &i);
	while (i < argc)
	{
		if (ft_strequ(argv[i], "-n"))
			add_player_with_number(e, argv[i + 1], argc, &i);
		else
			add_player_empty(e, &i, e->num_players);
		e->num_players += 1;
		if (e->num_players > MAX_PLAYERS)
			error_exit(e, 8);
		i++;
	}
	e->cursors = e->num_players;
}

static void	declare_winner(t_env *env)
{
	if (env->last_live_name)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		env->last_live_num * -1,
		env->last_live_name);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		((t_player*)env->players->content)->prog_num * -1,
		((t_player*)env->players->content)->name);
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
	load_programs(env, ++argv);
	run_game(env);
	declare_winner(env);
	ft_printf("cycle_to_die %d\n", env->cycle_to_die);
	ft_printf("total cycles %d\n", env->total_cycles);
	SAFE_DELETE(board);
	return (0);
}
