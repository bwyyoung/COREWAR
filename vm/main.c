/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/13 16:21:32 by mda-cost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "mgr_graphics.h"

t_bool		add_option(t_env *e, char **argv, int *i, int argc)
{
	if (ft_strequ(argv[*i], "-dump"))
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
	else if (ft_strequ(argv[*i], "-a"))
		return (e->options[a] = t_true);
	return (t_false);
}

int			count_players(t_env *env, t_player *player)
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

void		parse_flags(t_env *e, int argc, char **argv)
{
	int			i;

	i = 0;
	while (++i < argc)
	{
		if (!add_option(e, argv, &i, argc) && (i < argc))
			if (ft_strequ(argv[i], "-n"))
				add_player(e, argv,
					get_player_number(e, argv[i + 1], &i, argc), &i);
			else
				add_player(e, argv, -1, &i);
	}
}

void		init(t_env *env, t_env *backup)
{
	if (env->options[visual])
		graphics_loop(env, backup);
	else
	{
		introduce_players(env);
		run_game(env);
		declare_winner(env);
	}
}

int			main(int argc, char *argv[])
{
	t_env *backup;
	t_env *env;

	if (argc < 2)
	{
		print_instructions();
		return (0);
	}
	backup = create_env();
	parse_flags(backup, argc, argv);
	backup->num_players = count_players(backup, backup->lst_players);
	backup->op_tab = get_op_tab();
	load_players(backup);
	env = create_env();
	cpy_env(env, backup);
	srand(time(NULL));
	init(env, backup);
	SAFE_DELETE(env->op_tab);
	delete_env(env);
	lst_process_clr(backup);
	SAFE_DELETE(backup);
	return (0);
}
