/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_index_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 14:47:50 by douglas           #+#    #+#             */
/*   Updated: 2017/11/06 12:34:02 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_index_verbosity_four(t_env *env, t_process *process,
										int pc, t_index_info *index_info)
{
	int pc_and_mod;

	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s %d %d r%d\n",
												process->process_num,
												env->op_tab[process->op].name,
												index_info->index1,
												index_info->index2,
												process->param_val[2]);
	P(env->g_ref, env->options[visual], "       | -> load from %d + %d = %d",
												index_info->index1,
												index_info->index2,
												index_info->index_sum);
	pc_and_mod = (pc + (index_info->index_sum % IDX_MOD));
	if (pc_and_mod < 0 && pc_and_mod < index_info->index_sum)
		pc_and_mod += MEM_SIZE;
	if (process->op == lldi)
		P(env->g_ref, env->options[visual], " (with pc %d)\n",
												pc + index_info->index_sum);
	else
		P(env->g_ref, env->options[visual], " (with pc and mod %d)\n",
												pc_and_mod);
}

/*
** ldi adds its params P1 and P2 and converts that sum to an idx_val.
** It then uses the idx_val to read REG_SIZE bytes from the board.
** It then loads the val it has read from the board into the P3 register.
**
** lldi works the same but it does not convert the sum into an idx_val.
**
** (T_REG | T_DIR | T_IND) , (T_DIR | T_REG), T_REG
*/

void		op_index_load(t_env *env, t_process *process, int pc)
{
	int				index1;
	int				index2;
	int				index_sum;
	int				new_reg_val;
	t_index_info	*index_info;

	if (process->param_type[1] == IND_CODE
			|| process->param_type[2] != REG_CODE)
		return ;
	if (check_param_reg_nums(process))
		return ;
	index1 = get_param_val(env, 0, process, REG_SIZE);
	index2 = get_param_val(env, 1, process, REG_SIZE);
	index_sum = index1 + index2;
	if (process->op == ldi)
		index_sum %= IDX_MOD;
	new_reg_val = get_board_val(env->board, pc + index_sum, REG_SIZE);
	set_reg_val(process, process->param_val[2], new_reg_val);
	if (process->op == lldi)
		modify_carry(process, new_reg_val);
	index_info = create_index_info(index1, index2, index1 + index2);
	print_index_verbosity_four(env, process, pc, index_info);
	SAFE_DELETE(index_info);
}
