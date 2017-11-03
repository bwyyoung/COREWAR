/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:59:21 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 20:53:28 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** aff will print the ASCII representation of the value in the
** register it gets as a parameter.
** PARAM_TYPES: T_REG
*/

void		op_aff(t_env *env, t_process *process, int pc)
{
	int reg_num;

	reg_num = get_board_val(env->board, pc + 2, 1);
	if (valid_reg_num(reg_num) && env->options[a])
	{
		P(env->g_ref, env->options[visual], "AFF: %c\n",
		get_reg_val(process, reg_num) % 256);
	}
}
