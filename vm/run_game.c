/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/12 16:16:11 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_lives(t_env *env)
{
	if (env->total_lives >= NBR_LIVE || env->checks == MAX_CHECKS - 1)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		// ft_printf("CYCLE TO DIE IS NOW %d\n", env->cycle_to_die);
		env->checks = 0;
	}
	else
		env->checks++;
	env->cycles_since_check = 0;
	env->total_lives = 0;
}

void		run_game(t_env *env)
{
	while (1)
	{
		if (env->cycles_since_check >= env->cycle_to_die)
		{
			check_lives(env);
			kill_processes(env);
		}
		if (env->processes == NULL)
			break;
		if (env->options[d] == 1 && env->option_num == env->total_cycles)
		{
			dump_memory(env);
			break;
		}
		if (env->options[s] == 1 && (env->total_cycles % env->option_num) == 0)
		{
			dump_memory(env);
			ft_printf("total %d\n", env->total_cycles);
		}
		execute_cycle(env);
		// ft_printf("IT IS NOW CYCLE %d\n", env->total_cycle);
		env->total_cycles++;
		env->cycles_since_check++;
	}
}
