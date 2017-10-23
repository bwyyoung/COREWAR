/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:13:32 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/20 10:36:48 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		perform_check(t_env *env)
{
	ft_printf("perform_check\n");
	if (env->lives_since_check >= NBR_LIVE || env->checks == MAX_CHECKS - 1)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		// ft_printf("CYCLE TO DIE IS NOW %d\n", env->cycle_to_die);
		env->checks = 0;
	}
	else
		env->checks++;
	env->cycles_since_check = 0;
	env->lives_since_check = 0;
	kill_processes(env);
}

/*
** This is the main game loop.
** The game ends when all of the processes have died (env->processes == NULL)
** Every time cycles_since_check is >= cycle_to_die we have to
** perform check. During the check all the processes that didn't execute the
** live command will be deleted.
*/
void		run_game(t_env *env)
{
	while (1)
	{
		if (env->cycles_since_check >= env->cycle_to_die)
			perform_check(env);
		if (env->processes == NULL)
			break;
		if (env->options[d] == 1 && env->dump_value == env->total_cycles)
		{
			dump_memory(env);
			break;
		}
		if (env->options[s] == 1 && (env->total_cycles % env->cycle_value) == 0)
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
