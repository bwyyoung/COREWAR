/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:18:48 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 18:07:09 by dengstra         ###   ########.fr       */
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
	if (process->param_type[0] == IND_CODE && process->op == lld)
		new_reg_val = get_param_val(env, 0, process, IND_SIZE);
		// new_reg_val = (int16_t)get_param_val(env, 0, process, IND_SIZE);
	else
		new_reg_val = get_param_val(env, 0, process, REG_SIZE);
	set_reg_val(process, process->param_val[1], new_reg_val);
	modify_carry(process, new_reg_val);
	print_verbosity_four(env, process, process->op, new_reg_val);
}

static void	print_index_verbosity_four(t_env *env, t_process *process,
										int pc, t_index_info *index_info)
{
	int pc_and_mod;

	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->g_ref, env->options[visual], "P %4u | %s ", process->process_num,
								env->op_tab[process->op].name);
	P(env->g_ref, env->options[visual], "%d ", index_info->index1);
	P(env->g_ref, env->options[visual], "%d ", index_info->index2);
	P(env->g_ref, env->options[visual], "r%d\n", process->param_val[2]);
	P(env->g_ref, env->options[visual], "       | -> load from %d + %d = %d",
											index_info->index1,
											index_info->index2,
											index_info->index_sum);
	pc_and_mod = (pc + (index_info->index_sum % IDX_MOD));
	if (pc_and_mod < 0 && pc_and_mod < index_info->index_sum)
		pc_and_mod += MEM_SIZE;
	if (process->op == lldi)
		P(env->g_ref, env->options[visual], " (with pc %d)\n",
			(pc + index_info->index_sum));
	else
		P(env->g_ref, env->options[visual], " (with pc and mod %d)\n",
			pc_and_mod);
}

static int	get_new_reg_val(t_env *env, t_process *process, int index_sum)
{
	if (process->op == ldi)
		return (get_board_val(env->board, (process->regs[0]
					+ (index_sum % IDX_MOD)), REG_SIZE));
	else
		return (get_board_val(env->board, (process->regs[0]
					+ index_sum), REG_SIZE));
}

/*
** ldi adds its params P1 and P2 and converts that sum to an idx_val.
** It then uses the idx_val to read REG_SIZE bytes from the board.
** It then loads the val it has read from the board into the P3 register.
**
** lldi works the same but it does not convert the val into an idx_val.
**
** (T_REG | T_DIR | T_IND) , (T_DIR | T_REG), T_REG
*/

void		op_index_load(t_env *env, t_process *process)
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
	new_reg_val = get_new_reg_val(env, process, index_sum);
	set_reg_val(process, process->param_val[2], new_reg_val);
	if (process->op == lldi)
		modify_carry(process, new_reg_val);
	index_info = create_index_info(index1, index2, index_sum);
	print_index_verbosity_four(env, process, process->regs[0], index_info);
	SAFE_DELETE(index_info);
}
