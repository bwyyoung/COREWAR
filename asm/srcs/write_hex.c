/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 19:22:16 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/19 16:41:35 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../includes/op.h"
#include "../includes/asm.h"

static void		add_ind(t_env *env, t_token *param, int start)
{
	uint16_t	ind;
	int			i;

	i = 0;
	ind = 0;
	if (param->value[0] != LABEL_CHAR)
		ind = ft_atoi(param->value);
	else
	{
		while (i < env->label_count &&
			ft_strcmp(&param->value[1], env->labels[i]->name->value))
			i++;
		if (i == env->label_count)
			ft_error(param, env, "Label not defined.");
		ind = env->labels[i]->addr - start;
	}
	ft_memcpy(env->str + env->pc, &ind, sizeof(uint16_t));
	reverse_bytes(env->str, env->pc, 2);
	env->pc = env->pc + 2;
}

static void		add_dir(t_env *env, t_inst *inst, t_token *param, int start)
{
	int			i;
	int			size;
	uint32_t	dir;

	i = 0;
	dir = 0;
	size = get_op_by_opcode(inst->opcode)->label_size ? 2 : 4;
	if (param->value[0] != LABEL_CHAR)
		dir = ft_atoi(param->value);
	else
	{
		while (i < env->label_count &&
			ft_strcmp(&param->value[1], env->labels[i]->name->value))
			i++;
		if (i == env->label_count)
			ft_error(param, env, "Label not defined.");
		dir = env->labels[i]->addr - start;
	}
	ft_memcpy(env->str + env->pc, &dir, size);
	reverse_bytes(env->str, env->pc, size);
	env->pc = env->pc + size;
}

static void		ft_add_inst_bytes(t_env *env, t_inst *inst, int start)
{
	int			i;
	t_token		*param;
	char		*str;

	i = 0;
	str = env->str;
	param = inst->params;
	str[env->pc++] = inst->opcode;
	if (inst->type)
		str[env->pc++] = inst->type;
	while (i < inst->pcount)
	{
		if (param->type == T_REG)
		{
			env->str[env->pc] = (char)ft_atoi(param->value + 1);
			env->pc = env->pc + 1;
		}
		else if (param->type == T_DIR)
			add_dir(env, inst, param, start);
		else if (param->type == T_IND)
			add_ind(env, param, start);
		if (++i < inst->pcount)
			param = param->next->next;
	}
}

static void		fill_header(t_env *env)
{
	t_header	*header;
	t_token		*str;

	if (!(header = (t_header *)malloc(sizeof(t_header))))
		ft_exit("Malloc Error.");
	header->magic = COREWAR_EXEC_MAGIC;
	header->prog_size = env->pc;
	str = env->token->next;
	if (ft_strlen(str->value) > PROG_NAME_LENGTH)
		ft_error(str, env, "Program name too big.");
	ft_strcpy(header->prog_name, str->value);
	str = str->next->next;
	if (ft_strlen(str->value) > COMMENT_LENGTH)
		ft_error(str, env, "Comment is too big.");
	ft_strcpy(header->comment, str->value);
	reverse_bytes((char *)header, 0, 4);
	reverse_bytes((char *)&header->prog_size, 0, 4);
	env->header = header;
}

void			ft_write_hex(t_env *env)
{
	t_inst	*inst;
	char	*str;
	int		fd;

	if (!(str = (char *)malloc(sizeof(char) * env->pc + 1)))
		ft_exit("Malloc Error.");
	fill_header(env);
	env->pc = 0;
	env->str = str;
	inst = env->inst;
	while (inst)
	{
		ft_add_inst_bytes(env, inst, env->pc);
		inst = inst->next;
	}
	fd = open(env->filename, O_WRONLY | O_TRUNC | O_CREAT,
		S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	write(fd, env->header, sizeof(t_header));
	write(fd, str, env->pc);
	close(fd);
}
