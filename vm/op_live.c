/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:22:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/06 13:03:37 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		print_verbosity_four(t_env *env, t_process *process)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | live %d\n",
								process->process_num,
								process->param_val[0]);
}

t_player		*add_live(t_env *env, int prog_num)
{
	t_player *cur_player;

	cur_player = env->lst_players;
	while (cur_player)
	{
		if ((uint32_t)prog_num == cur_player->prog_num)
		{
			cur_player->lives++;
			break ;
		}
		cur_player = cur_player->next;
	}
	return (cur_player);
}

/*
** A processes needs to call the live op once before a check or it will die.
** It does not matter for the process what the param is,
** but the param matters to the player.
** If the param matches the player's number the player is now the last
** player to have gotten a live.
** The last player at the end of the game that has gotten a live wins.
*/

void			op_live(t_env *env, t_process *process)
{
	t_player *player;

	if ((player = add_live(env, process->param_val[0])))
	{
		if (env->options[v] && env->verbose_value == 1)
			P(env->g_ref, env->options[visual],
				"Player %d (%s) is said to be alive\n",
					player->prog_num * -1, player->name);
		env->last_live_num = player->prog_num;
		env->last_live_name = player->name;
	}
	process->lives++;
	env->lives_since_check++;
	print_verbosity_four(env, process);
	process->last_live = 0;
}
