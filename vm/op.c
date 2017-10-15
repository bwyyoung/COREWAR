/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/10/15 19:38:12 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op	g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 10, 0, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 0, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
					1, 0, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
					1, 0, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
					6, 1, 0, 4},
	{"zjmp", 1, {T_DIR}, 20, 0, 1, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25, 1, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25, 1, 1, 2},
	{"fork", 1, {T_DIR}, 800, 0, 1, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 0, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50, 1, 1, 2},
	{"lfork", 1, {T_DIR}, 1000, 0, 1, 2},
	{"aff", 1, {T_REG}, 2, 1, 0, 0},
};

char		*get_op_name_test(uint8_t op)
{
	return (ft_strdup(g_op_tab[op].name));
}

static int	is_invalid_op(t_process *process, uint8_t op)
{
	int is_invalid;

	is_invalid = 0;
	if (op > aff)
	{
		inc_pc(process->regs, 1);
		is_invalid = 1;
	}
	return (is_invalid);
}

uint32_t	get_cycles(t_env *env, t_process *process)
{
	uint8_t		op;

	op = env->board[process->regs[0]];
	if (is_invalid_op(process, op))
		return (0);
	return (g_op_tab[op].cycles);
}

uint32_t	get_label_size(t_env *env, t_process *process)
{
	uint8_t		op;

	op = env->board[process->regs[0]];
	if (is_invalid_op(process, op))
		return (0);
	return (g_op_tab[op].label_size);
}

int			validate_types(uint8_t op, uint8_t types)
{
	t_op	op_info;
	int		i;
	int		num_types;
	uint8_t	type;

	op_info = g_op_tab[op];
	if (op_info.has_type == 0)
		return (0);
	if (op > aff || types == 0)
		return (1);
	num_types = op_info.argc;
	i = 0;
	while (num_types--)
	{
		type = types >> (num_types * 2);
		type = types & 0b00000011;
		if (type != (type & op_info.arg_types[num_types]))
			return (1);
		types = types << 2;
	}
	return (0);
}
