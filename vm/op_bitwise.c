/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:03:47 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/17 00:47:05 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

label_size 4
*/

// void			op_and(t_env *env, t_process *process)
// {
// 	bitwise(env, process, and);
// }

/*
or: This operation is an bit-to-bit OR, in the same spirit and principle of and, its
opcode is obviously 7.
(T_REG | T_IND | T_DIR), (T_REG | T_IND | T_DIR), T_REG

label_size 4
*/

// void			op_or(t_env *env, t_process *process)
// {
// 	bitwise(env, process, or);
// }

/*
xor: Acts like and with an exclusive OR. As you will have guessed, its opcode in
octal is 10.
(T_REG | T_IND | T_DIR), (T_REG | T_IND | T_DIR), T_REG

label_size 4
*/

// void			op_xor(t_env *env, t_process *process)
// {
// 	bitwise(env, process, xor);
// }
