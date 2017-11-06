/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:16:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/05 14:27:01 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process)
{
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s r%d %d\n",
				process->process_num,
				env->op_tab[process->op].name,
				process->param_val[0],
				(int16_t)process->param_val[1]);
}

/*
** st takes a register and stores its value either on the board or
** in another registry.
**
** T_REG, (T_IND | T_REG)
*/

void		op_store(t_env *env, t_process *process, int pc)
{
	int	reg_val;
	int	param_val;

	if (process->param_type[0] != REG_CODE
		|| process->param_type[1] == DIR_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	reg_val = get_reg_val(process, process->param_val[0]);
	param_val = process->param_val[1];
	if (process->param_type[1] == REG_CODE)
		set_reg_val(process, param_val, reg_val);
	else
		set_board_val(env, process,
				pc + ((int16_t)param_val % IDX_MOD), reg_val);
	print_verbosity_four(env, process);
}
