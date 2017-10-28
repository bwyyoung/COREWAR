/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 20:31:02 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/28 17:42:51 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_verbosity_four(t_env *env, t_process *process)
{
	int16_t		index;
	uint32_t	pc;

	index = process->param_val[0];
	pc = process->regs[0];
	if (!env->options[v] || env->verbose_value != 4)
		return ;
	P(env->options[visual], "P %4u | %s %d ", process->process_num,
								get_op_name(process->op), index);
	if (process->op == lfork)
		P(env->options[visual], "(%d)\n", pc + index);
	else
		P(env->options[visual], "(%d)\n", pc + get_idx_val(index));
}

/*
** Creates a new process. The new process will be the same except for the pc and cycles_left.
** The difference between fork and lfork is that fork will use a idx_val to increase the pc
** while lfork will just use the ind_val directly.
**
** T_DIR
*/

void			fork_variables(t_process *cpy, t_process *original, t_env *e)
{
	cpy->types = original->types;
	cpy->carry = original->carry;
	cpy->name = original->name;
	cpy->prog_num = original->prog_num;
	cpy->lives = original->lives;
	cpy->op = original->op;
	cpy->process_num = e->num_processes + 1;
	cpy->cycles_left = 0;
	cpy->param_type[0] = 0;
	cpy->param_type[1] = 0;
	cpy->param_type[2] = 0;
	cpy->param_val[0] = 0;
	cpy->param_val[1] = 0;
	cpy->param_val[2] = 0;
	cpy->last_live = original->last_live;
	e->j = -1;
	while (e->j++ < REG_NUMBER)
		cpy->regs[e->j] = original->regs[e->j];
}

void			op_forker(t_env *env, t_process *process, int op)
{
	if (!(env->new_fork = create_process(env)))
		ft_error_errno(NULL);
	fork_variables(env->new_fork, process, env);
	if (op == lfork)
		inc_pc(env->new_fork, process->param_val[0]);
	else
		inc_pc(env->new_fork, get_idx_val((int16_t)process->param_val[0]));
	lst_process_add(env, env->new_fork);
	print_verbosity_four(env, process);
}

/*
fork

//epitech
fork:
This instruction is not followed by a parameter encoding byte.
It always takes an index and creates a new program,
which is executed from address : (PC + (first parameter % IDX_MOD)).
Fork %34 creates a new program. The new program inherits all of its father’s states.

//42
there is no argument’s coding byte, take an index, opcode 0x0c. Create a
new process that will inherit the different states of its father, except its PC, which
will be put at (PC + (1st parameter % IDX_MOD)).

*/

/*
lfork:
Same as fork, without the % IDX_MOD This operation modifies the carry.
*/