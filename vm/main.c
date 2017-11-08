/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/08 17:22:33 by dengstra         ###   ########.fr       */
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
				add_player(e, argv, get_player_number(e, argv[i + 1], &i, argc), &i);
			else
				add_player(e, argv, -1, &i);
	}
}

void		init(t_env *env, t_env *backup)
{
	if (env->options[visual])
	{
		graphics_loop(env, backup);
	}
	else
	{
		introduce_players(env);
		run_game(env);
		declare_winner(env);
	}
}

void		delete_env(t_env *env)
{
	lst_process_clr(env);
	lst_players_clr(env);
	SAFE_DELETE(env);
}

void		cpy_env(t_env *dst, t_env *src)
{
	ft_bzero(dst, sizeof(t_env));
	dst->cycle_to_die = CYCLE_TO_DIE;
	dst->to_die = CYCLE_TO_DIE;
	dst->lst_process = NULL;
	dst->num_players = src->num_players;
	dst->op_tab = src->op_tab;
	dst->lst_players = src->lst_players;
	dst->lst_process = NULL;
	dst->last_live_name = NULL;
	ft_memcpy(dst->options, src->options, sizeof(int) * 10);
	dst->verbose_value = src->verbose_value;
	dst->dump_value = src->dump_value;
	dst->cycle_value = src->cycle_value;
	lst_process_clr(src);
	load_players(dst);
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
	load_players(backup);
	env = create_env();
	cpy_env(env, backup);
	srand(time(NULL));
	init(env, backup);
	delete_env(env);
	lst_process_clr(backup);
	SAFE_DELETE(backup);
	return (0);
}
