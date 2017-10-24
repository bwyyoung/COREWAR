/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:16:45 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/23 21:48:45 by douglas          ###   ########.fr       */
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
	ft_printf("0x0000 : ");
	while (mem_size)
	{
		if (mem_size % 0x40 == 0 && i >= 0x40)
		{
			hex += 0x40;
			ft_printf("\n0x%04x : ", hex);
		}
		ft_printf("%02x ", board[i]);
		i++;
		mem_size--;
	}
	ft_printf("\n");
}
