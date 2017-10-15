/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_get_sizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 18:16:05 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/14 16:37:06 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t	get_arg_size(uint8_t type, int label_size)
{
	uint32_t size;

	size = 0;
	if (type == REG_CODE)
		size = 1;
	else if (type == DIR_CODE)
		size = label_size;
	else if (type == IND_CODE)
		size = IND_SIZE;
	return (size);
}

uint32_t	get_op_size(t_env *env, t_process *process)
{
	uint32_t	size;
	uint8_t		types;

	types = process->types;
	size = 2;
	while (types)
	{
		size += get_arg_size(types & 0b00000011, get_label_size(env, process));
		types = types >> 2;
	}
	return (size);
}
