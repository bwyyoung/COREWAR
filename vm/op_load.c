/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:18:48 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/07 14:18:02 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process,
											int op, int new_reg_val)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s %d r%d\n",
								process->process_num,
								env->op_tab[op].name,
								new_reg_val,
								process->param_val[1]);
}

/*
** ld: Take a param and load it into a registry(P2)
** lld: The same as ld but doesn't use IDX_MOD
** (T_DIR | T_IND), T_REG
*/

void		op_load(t_env *env, t_process *process)
{
	int		new_reg_val;

	if (process->param_type[0] == REG_CODE
			|| process->param_type[1] != REG_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	new_reg_val = get_param_val(env, process, 0);
	set_reg_val(process, process->param_val[1], new_reg_val);
	modify_carry(process, new_reg_val);
	print_verbosity_four(env, process, process->op, new_reg_val);
}
