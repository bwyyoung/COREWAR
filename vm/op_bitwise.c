/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:03:47 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/18 17:23:34 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Apply a bitwise operation on the two first params and store the result in a
** register(P3).
**
** P3 = P1 & P2
** PARAM_TYPES: (T_REG | T_DIR | T_IND), (T_REG | T_IND | T_DIR), T_REG
*/

void		op_bitwise(t_env *env, t_process *process, int op)
{
	uint32_t val1;
	uint32_t val2;
	uint32_t result;

	val1 = get_param_val(env->board, process->params[0], process, IND_SIZE);
	val2 = get_param_val(env->board, process->params[1], process, IND_SIZE);
	if (op == and)
		result = val1 & val2;
	else if (op == or)
		result = val1 | val2;
	else
		result = val1 ^ val2;
	set_reg_val(process, process->params[2].val, result);
	modify_carry(process, result);
}

/*
and: Apply an & (bit-to-bit AND) over the first two arguments and store the result
in a registry, which is the third argument. Opcode 0x06. Modifies the carry.
(T_REG | T_DIR | T_IND), (T_REG | T_IND | T_DIR), T_REG


or: This operation is an bit-to-bit OR, in the same spirit and principle of and, its
opcode is obviously 7.
(T_REG | T_IND | T_DIR), (T_REG | T_IND | T_DIR), T_REG


xor: Acts like and with an exclusive OR. As you will have guessed, its opcode in
octal is 10.
(T_REG | T_IND | T_DIR), (T_REG | T_IND | T_DIR), T_REG

*/

