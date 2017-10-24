/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:13:26 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 12:56:02 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process, int op)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	ft_printf("P    %u | %s ", process->process_num,
								get_op_name(op));
	print_verbosity_four_vals(process);
	ft_putchar('\n');
}

/*
** Takes three registers and adds or subs the two first registers values, and then stores it in the third registry.
** P3 = P1 + P2
** PARAM TYPES: T_REG, T_REG, T_REG
*/

void		op_arithmetic(t_env *env, t_process *process, int op)
{
	uint32_t	reg_val1;
	uint32_t	reg_val2;
	uint32_t	result;
	uint32_t	reg_num1;
	uint32_t	reg_num2;

	if (check_param_reg_nums(process, 1, 1, 1))
		return ;
	reg_num1 = process->param_val[0];
	reg_num2 = process->param_val[1];
	if (valid_reg_num(reg_num1) && valid_reg_num(reg_num2)) // test what happens when reg_num is invalid
	{
		reg_val1 = get_reg_val(process, reg_num1);
		reg_val2 = get_reg_val(process, reg_num2);
		result = 0;
		if (op == add)
			result = reg_val1 + reg_val2; // Does not handle overflow!!!
		else if (op == sub)
			result = reg_val1 - reg_val2; // Does not handle overflow!!!
		set_reg_val(process, process->param_val[2], result);
		modify_carry(process, result);
	}
	print_verbosity_four(env, process, op);
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
