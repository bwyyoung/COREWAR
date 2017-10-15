/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:22:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/13 18:10:23 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		add_live(t_env *env, char *name)
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
live: The instruction that allows a process to stay alive. It can also record that
the player whose number is the argument is indeed alive. No argument’s coding
byte, opcode 0x01. Oh and its only argument is on 4 bytes.

labe_size 4
*/

void			op_live(t_env *env, t_process *process, uint32_t pc)
{
	uint32_t	prog_num;
	uint8_t		*board;

	board = env->board;
	prog_num = get_board_val(board, pc + 1, 4);
	if (prog_num == process->prog_num)
	{
		add_live(env, process->name);
		// ft_printf("A process shows that player %d (%s) is alive\n", process->prog_num, process->name);
		env->last_live_num = process->prog_num;
		env->last_live_name = process->name;
	}
	process->lives++;
	env->total_lives++;
	inc_pc(process->regs, 5);
}
