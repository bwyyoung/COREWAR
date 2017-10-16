/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:01:59 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/17 00:17:07 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	get_board_val(uint8_t *board, uint32_t index, uint32_t size)
{
	uint8_t			*pval;
	uint32_t		val;
	int				i;

	val = 0;
	i = 0;
	pval = (uint8_t*)&val;
	while (size--)
	{
		pval[i] = board[(index + size) % MEM_SIZE];
		// pval[size] = board[(index + i) % MEM_SIZE];
		// ft_printf("size %d, val %x\n", size, pval[i]);
		i++;
	}
	return (val);
}

void		set_board_val(uint8_t *board, uint32_t index, uint32_t size,
							uint32_t val)
{
	uint8_t		*pval;

	pval = (uint8_t*)&val;
	while (size--)
	{
		board[index % MEM_SIZE] = pval[size];
		index++;
	}
}
