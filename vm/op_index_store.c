/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_index_store.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 14:22:00 by douglas           #+#    #+#             */
/*   Updated: 2017/11/05 14:44:43 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_index_verbosity_four(t_env *env, t_process *process,
										int pc, t_index_info *index_info)
{
	int pc_and_mod;

	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s ", process->process_num,
								env->op_tab[process->op].name);
	if (process->param_type[0] == REG_CODE)
		ft_putchar('r');
	P(env->g_ref, env->options[visual], "%d %d %d\n", process->param_val[0],
											index_info->index1,
											index_info->index2);
	pc_and_mod = (pc + (index_info->index_sum % IDX_MOD));
	if (pc_and_mod < 0 && pc_and_mod < index_info->index_sum)
		pc_and_mod += MEM_SIZE;
	P(env->g_ref, env->options[visual],
	"       | -> store to %d + %d = %d (with pc and mod %d)\n",
	(index_info->index1),
	(index_info->index2),
	(index_info->index_sum),
	pc_and_mod);
}

/*
** sti adds its params P2 and P3 and converts that sum to an idx_val.
** It then uses that idx_val as an index to decide where on the board
** to write the value of P1 (REG).
**
** T_REG, (T_REG | T_DIR | T_IND), (T_DIR | T_REG)
*/

void		op_index_store(t_env *env, t_process *process, int pc)
{
	int				index1;
	int				index2;
	int				index_sum;
	int				new_reg_val;
	t_index_info	*index_info;

	if (process->param_type[0] != REG_CODE
		|| process->param_type[2] == IND_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	index1 = get_param_val(env, 1, process, REG_SIZE);
	index2 = get_param_val(env, 2, process, REG_SIZE);
	index_sum = index1 + index2;
	new_reg_val = get_reg_val(process, process->param_val[0]);
	set_board_val(env, process, pc + (index_sum % IDX_MOD), new_reg_val);
	index_info = create_index_info(index1, index2, index_sum);
	print_index_verbosity_four(env, process, pc, index_info);
	SAFE_DELETE(index_info);
}
