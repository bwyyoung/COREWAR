/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/11 20:31:09 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_memory(t_env *env)
{
	uint8_t		*board;
	int			mem_size;
	int			i;
	int			hex;

	board = env->board;
	mem_size = MEM_SIZE;
	i = 0;
	hex = 0;
	P(env->g_ref, env->options[visual], "0x0000 : ");
	while (mem_size)
	{
		if (mem_size % 32 == 0 && i >= 32)
		{
			hex += 32;
			P(env->g_ref, env->options[visual], "\n0x%04x : ", hex);
		}
		P(env->g_ref, env->options[visual], "%02x ", board[i]);
		i++;
		mem_size--;
	}
	P(env->g_ref, env->options[visual], "\n");
}
