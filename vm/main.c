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

void		add_option(t_env *env, char *option)
{
	if (ft_strequ(option, "-d"))
		env->options[d] = 1;
	if (ft_strequ(option, "-s"))
		env->options[s] = 1;	
}

void		handle_args(t_env *env, int argc, char *argv[])
{
	int i;

	i = 0;
	while (argv[i + 1])
	{
		if (argv[i][0] == '-')
		{
			add_option(env, argv[i]);
			env->option_num = ft_atoi(argv[i + 1]);
			argc -= 2;
		}
		i++;
	}
	env->num_players = argc - 1;
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
		return (0);
	board = create_board();
	env = create_env(board);
	handle_args(env, argc, argv);
	load_programs(env, ++argv);
	run_game(env);
	declare_winner(env);
	ft_printf("cycle_to_die %d\n", env->cycle_to_die);
	ft_printf("total cycles %d\n", env->total_cycles);
	free(board);
	return (0);
}
