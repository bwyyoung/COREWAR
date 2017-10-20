/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:13:26 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/19 15:26:11 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Takes three registers and adds or subs the two first registers values, and then stores it in the third registry.
** P3 = P1 + P2
** PARAM TYPES: T_REG, T_REG, T_REG
*/

void		op_arithmetic(t_env *env, t_process *process, int op)
{
	int			reg_val1;
	int			reg_val2;
	int			result;
	int			reg_num1;
	int			reg_num2;

	(void)env;
	reg_num1 = process->params[0].val;
	reg_num2 = process->params[1].val;
	if (valid_reg_num(reg_num1) && valid_reg_num(reg_num2)) // test what happens when reg_num is invalid
	{
		reg_val1 = get_reg_val(process, reg_num1);
		reg_val2 = get_reg_val(process, reg_num2);
		result = 0;
		if (op == add)
			result = reg_val1 + reg_val2; // Does not handle overflow!!!
		else if (op == sub)
			result = reg_val1 - reg_val2; // Does not handle overflow!!!
		set_reg_val(process, process->params[2].val, result);
		modify_carry(process, result);
	}
}

/*
// 42
add: Opcode 4. Take three registries, add the first two, and place the result in the
third, right before modifying the carry.

// epitech
This instruction takes 3 registers as parameter,
subs the contents of the 2 first and stores the result in the third.
This operation modifies the carry.
sub r2,r3,r5 subs r2 and r3 and stores the result in r5
*/
