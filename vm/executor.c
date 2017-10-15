/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:10:13 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/14 18:13:00 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	get_types(t_process *process, uint8_t types, uint8_t op)
{
	if (validate_types(op, types))
	{
		inc_pc(process->regs, 2);
		return (1);
	}
	process->types = types;
	return (0);
}

static void	execute_op(t_env *env, t_process *process)
{
	uint8_t			op;
	int				pc;

	pc = process->regs[0];
	op = env->board[pc];
	if (get_types(process, env->board[(pc + 1) % MEM_SIZE], op))
		return ;
	if (op == live)
		op_live(env, process, pc);
	else if (op == ld || op == lld)
		op_basic_load(env, process, op);
	else if (op == st || op == sti)
		op_store(env, process, pc, op);
	else if (op == add || op == sub)
		op_arithmetic(env, process, op);
	else if (op == and || op == or || op == xor)
		op_bitwise(env, process, op);
	else if (op == zjmp)
		op_zjmp(env, process, pc);
	else if (op == ldi || op == lldi)
		op_index_load(env, process, op);
	else if (op == e_fork || op == lfork)
		op_forker(env, process, pc, op);
	else if (op == aff)
		op_aff(env, process, pc);
}

static void	execute_process(t_process *process, t_env *env)
{
	if (process->cycles_left == 1)
	{
		execute_op(env, process);
		process->cycles_left = 0;
	}
	else if (process->cycles_left <= 0)
	{
		if (env->board[process->regs[0]] != 0)
		{
			process->cycles_left = get_cycles(env, process) - 1;
		}
		else
			inc_pc(process->regs, 1);
	}
	else
		process->cycles_left--;
}

void		execute_cycle(t_env *env)
{
	t_list		*processes;
	uintmax_t	num_processes;

	processes = env->processes;
	num_processes = env->num_processes;
	// while (num_processes--)
	while (processes)
	{
		execute_process(processes->content, env);
		processes = processes->next;
	}
}
