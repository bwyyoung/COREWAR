/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:01:59 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 16:12:35 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Get a value from the board and reverse its endian.
** Example:
**		The number ff fb is stored as ff fb in C but
**		on the board it is stored as fb ff.
*/
uint32_t	get_board_val(uint8_t *board, uint32_t index, uint32_t size)
{
	uint8_t			*pval;
	uint32_t		val;
	int				i;

	val = 0;
	i = 0;
	pval = (uint8_t*)&val;
	while (size--)
		pval[i++] = board[(index + size) % MEM_SIZE];
	return (val);
}

/*
** Set a value on the board. Though before writing it we have to reverse its endian.
** This is because the endian is different between C and the board.
** Example:
**		The number ff fb is stored as ff fb in C but
**		on the board it is stored as fb ff.
*/
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
