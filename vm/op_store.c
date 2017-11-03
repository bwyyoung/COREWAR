/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:16:50 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/02 20:39:24 by dengstra         ###   ########.fr       */
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

void		op_st(t_env *env, t_process *process, int pc)
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

void		op_sti(t_env *env, t_process *process, int pc)
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

void		op_store(t_env *env, t_process *process, int pc, int op)
{
	if (op == sti)
		op_sti(env, process, pc);
	else
		op_st(env, process, pc);
}
