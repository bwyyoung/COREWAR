/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:59:21 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/17 00:50:18 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
aff:
The opcode is 10 in the hexadecimal. There is an argument’s coding byte,
even if it’s a bit silly because there is only 1 argument that is a registry, which is a
registry, and its content is interpreted by the character’s ASCII value to display on
the standard output. The code is modulo 256.
*/

void		op_aff(t_env *env, t_process *process, uint32_t pc)
{
	uint32_t reg_val;
	uint32_t reg_num;

	reg_num = get_board_val(env->board, pc + 2, 1);
	if (valid_reg_num(reg_num))
	{
		reg_val = get_reg_val(process, reg_num);
		ft_putchar(reg_val % 256);
	}
}
