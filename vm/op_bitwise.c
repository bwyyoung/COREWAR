/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:03:47 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/07 14:40:55 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process,
									int val1, int val2)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s %d %d r%d\n",
								process->process_num,
								env->op_tab[process->op].name,
								val1,
								val2,
								process->param_val[2]);
}

/*
** Apply a bitwise operation on the two first params and store the result in a
** register(P3).
**
** P3 = P1 & P2
** PARAM_TYPES: (T_REG | T_DIR | T_IND), (T_REG | T_IND | T_DIR), T_REG
*/

void		op_bitwise(t_env *env, t_process *process, int op)
{
	int val1;
	int val2;
	int result;

	if (process->param_type[2] != REG_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	val1 = get_param_val(env, process, 0);
	val2 = get_param_val(env, process, 1);
	if (op == and)
		result = val1 & val2;
	else if (op == or)
		result = val1 | val2;
	else
		result = val1 ^ val2;
	set_reg_val(process, process->param_val[2], result);
	modify_carry(process, result);
	print_verbosity_four(env, process, val1, val2);
}
