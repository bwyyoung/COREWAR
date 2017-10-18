/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:01:59 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/18 14:23:17 by dengstra         ###   ########.fr       */
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
