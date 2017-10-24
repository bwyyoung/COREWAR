/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:22:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 13:21:38 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			add_live(t_env *env, char *name)
{
	t_list *players;

	players = env->players;
	while (players)
	{
		if (ft_strequ(((t_player*)players->content)->name, name))
			((t_player*)players->content)->lives++;
		players = players->next;
	}
}

/*
**
** A processes needs to call the live op once before a check or it will die.
** It does not matter for the process what the param is, but the param matters to the player.
** If the param matches the player's number the player is now the last player to have gotten a live.
** The last player at the end of the game that has gotten a live wins.
**
*/

void			op_live(t_env *env, t_process *process)
{
	if (process->param_val[0] == process->prog_num)
	{
		add_live(env, process->name);
		// ft_printf("A process shows that player %d (%s) is alive\n", process->prog_num, process->name);
		env->last_live_num = process->prog_num;
		env->last_live_name = process->name;
	}
	process->lives++;
	env->lives_since_check++;
}

/*
// 42
live: The instruction that allows a process to stay alive. It can also record that
the player whose number is the argument is indeed alive. No argument’s coding
byte, opcode 0x01. Oh and its only argument is on 4 bytes.

// epitech
Followed by 4 bytes representing the player name.
This instruction indicates that the player is alive.
(No parameter encoding byte).
*/
