/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:47:13 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/15 17:16:25 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../includes/op.h"
#include "../includes/asm.h"

void	print_tokens(t_env *env)
{
	t_token		*token;

	token = env->token;
	while (token)
	{
		ft_printf("[line:col] = [%d:%d], Type : '%d', Value : '%s'\n", 
		token->pos->line, token->pos->col, token->type, token->value);
		token = token->next;
	}
}

void	print_labels(t_env *env)
{
	t_label		*label;
	int			i = 0;

	while (i < env->label_count)
	{
		label = env->labels[i];
		ft_printf("[line:col] = [%d:%d], LABEL : '%s', Addr : '%d'\n", 
		label->name->pos->line, label->name->pos->col, label->name->value, label->addr);
		i++;
	}
}

void	print_inst(t_env *env)
{
	t_inst		*inst;
	int			i = 0;

	inst = env->inst;
	while (inst)
	{
		ft_printf("%d\n", i++);
		// if (inst->label)
		// 	ft_printf("LABEL: '%s', ", inst->label->name->value);
		// else
		// 	ft_printf("NO LABEL, ");
		ft_printf("OPCODE = '%d', Type : '%d', size : '%d', pcount : '%d', params : '%s', line[%d:%d]\n", 
		inst->opcode, inst->type, inst->size, inst->pcount, inst->params->value, inst->params->pos->line, inst->params->pos->col);
		inst = inst->next;
	}
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;
	char	*temp;

	str = ft_strnew(len);
	if (!str)
		return (NULL);
	temp = str;
	while (len--)
		*temp++ = *src++;
	return (str);
}

char		*ft_concat(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		if (!(new = (char *)malloc(sizeof(char) * ft_strlen(s1) + 
		ft_strlen(s2) + 1)))
			return NULL;
		ft_strcpy(new, s1);
		ft_strcat(new, s2);
		free(s1);
	}
	return (new);
}

static t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
	 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7,
	 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8,
	 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 1},
	{"fork", 1, {T_DIR}, 12, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 0, 1},
	{"aff", 1, {T_REG}, 16, 1, 0},
	{0, 0, {0}, 0, 0, 0}
};

void		ft_exit(char *str)
{
	ft_putendl(str);
	exit(-1);
}

// void		ft_check_header(int fd, t_env *env)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	while(get_next_line(fd, &line) > 0)
// 	{
// 		env->line = env->line + 1;
// 		while(line && line[i] && (line[i] == ' ' || line[i] == '\t'))
// 			i++;
// 		if (line[i] != '.' && line[i] != '\0')
// 		{
// 			ft_printf("Lexical error [%d:%d]", env->line, i);
// 			ft_exit("");
// 		}
// 		else if (ft_strstr(line + i, NAME_CMD_STRING))
// 		{
// 			creat
// 		}
// 		free(line);
// 	}
// }

t_token		*create_token(t_env *env, int *col, char type, char *value)
{
	t_token		*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return NULL;
	if	(!(token->pos = (t_location *)malloc(sizeof(t_location))))
		return NULL;
	token->pos->line = env->line;
	token->pos->col = *col + 1;
	token->type = type;							//ft_strdup(type);
	token->value = ft_strdup(value);
	token->next = NULL;
	*col = *col + ft_strlen(value);
	return (token);
}

void		add_token(t_env *env, int *col, char type, char *value)
{
	t_token		*token;

	if (!(token = create_token(env, col, type, value)))
		ft_exit("Malloc Error.");
	if (env->last)
		env->last->next = token;
	else
		env->token = token;
	env->last = token;
}

void		check_command(t_env *env, char *line, int *col)//, int *quotation)
{
	if (ft_strstr(line + *col, NAME_CMD_STRING))
		add_token(env, col, '.', NAME_CMD_STRING);
	else if (ft_strstr(line + *col, COMMENT_CMD_STRING))
		add_token(env, col, '.', COMMENT_CMD_STRING);
	else
	{
		ft_printf("Lexical error at [%d:%d].", env->line, *col);
		ft_exit("");
	}
}

void		check_quotation(t_env *env, char *line, int *col, int *quotation)
{
	int		j;
	char	*str;

	j = 0;
	if (*quotation == 0)
		*col = *col + 1;
	// *quotation = 1;
	while (line[*col + j] && line[*col + j] != '"')
		j++;
	str = ft_strndup(line + *col, j);
	if (*quotation == 1)
	{
		// printf("Quotation : 1\n");
		env->last->value = ft_concat(env->last->value, "\n");
		env->last->value = ft_concat(env->last->value, str);
		*col = *col + j;
	}
	else
	{
		add_token(env, col, 32, str);
		*quotation = 1;
	}
	if (line[*col] == '"')
	{
		*quotation = 0;
		*col = *col + 1;
	}
	// printf("Quotation : 0000%d	line: '%s'\n", *quotation, line);
	// 	ft_printf("[line:col] = [%d:%d], Type : '%s', Value : '%s'\n", 
	// 	env->last->pos->line, env->last->pos->col, env->last->type, env->last->value);
	free(str);
}

void		check_direct(t_env *env, char *line, int *col)//, int *quotation)
{
	int		j;
	char	*str;

	j = 0;
	*col = *col + 1;
	if (line[*col] == LABEL_CHAR)
	{
		// *col = *col + 1;
		// while (line[*col + j] && line[*col + j] != LABEL_CHAR &&
		// line[*col + j] != SEPARATOR_CHAR && line[*col + j] != COMMENT_CHAR && 
		// line[*col + j] != DIRECT_CHAR && 
		// line[*col + j] != ' ' && line[*col + j] != '\t')
		while (line[*col + j + 1] && ft_strchr(LABEL_CHARS, line[*col + j + 1]))
			j++;
		str = ft_strndup(line + *col, j + 1);
		add_token(env, col, T_DIR, str);
	}
	else
	{
		if (line[*col + j] == '-')
			j++;
		while (line[*col + j] && ft_isdigit(line[*col + j]))
			j++;
		str = ft_strndup(line + *col, j);
		add_token(env, col, T_DIR, str);
	}
	free(str);
}

void		check_label(t_env *env, char *line, int *col, int j)
{
	char	*str;

	if (j == 0)
	{
		// *col = *col + 1;
		while (ft_strchr(LABEL_CHARS, line[*col + j + 1]))
			j++;
		str = ft_strndup(line + *col, j + 1);
		add_token(env, col, T_IND, str);
	}
	else
	{
		str = ft_strndup(line + *col, j);
		add_token(env, col, T_LAB, str);
		*col = *col + 1;
	}
	free(str);
}

int			check_op_by_name(char *name)
{
	int		i;
	
	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(name, op_tab[i].op))
			return (1);
		i++;
	}
	return (0);
}

void		check_op_reg(t_env *env, int *col, char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (check_op_by_name(str))
		add_token(env, col, 16, str);
	else if (str[0] == 'r')
	{
		nb = ft_atoi(str + 1);
		if (nb > 0 && nb <= REG_NUMBER)
			add_token(env, col, T_REG, str);
	}
	else if (i == ft_strlen(str))
		add_token(env, col, T_IND, str);
	else
	{
		add_token(env, col, 0, str);
		// ft_printf("Lexical error at [%d:%d].", env->line, *col + 1);
		// ft_exit("");
	}
}

void		check_token(t_env *env, char *line, int *col, int j)
{
	char	*str;

	if (j != 0)
	{
		str = ft_strndup(line + *col, j);
		check_op_reg(env, col, str);// "TOKEN", str);
	}
	else if (j == 0 && line[*col + j] == '-')
	{
		j++;
		while (ft_isdigit(line[*col + j]))
			j++;
		str = ft_strndup(line + *col, j);
		add_token(env, col, T_IND, str);
	}
	else
	{
		ft_printf("Lexical error at [%d:%d].", env->line, *col + 1);
		ft_exit("");
	}
	free(str);
}

void		generate_token(t_env *env, char *line, int *col, int *quotation)
{
	int		j;

	j = 0;
	if (line[*col] == '"' || *quotation == 1)
		check_quotation(env, line, col, quotation);
	// if (line[*col] == '.' && ft_strstr(line + col, NAME_CMD_STRING))
	// {
	// 	add_token(env, col, "CMD", NAME_CMD_STRING);
	// 	// *col = *col + ft_strlen(NAME_CMD_STRING);
	// }
	// else if (line[*col] == '.' && ft_strstr(line + col, COMMENT_CMD_STRING))
	// {
	// 	add_token(env, col, "CMD", COMMENT_CMD_STRING);
	// 	// *col = *col + ft_strlen(COMMENT_CMD_STRING);
	// }
	else if (line[*col] == '.')
		check_command(env, line, col);//, quotation);
		// ft_exit("Lexical error");
	// else if (line[*col] == LABEL_CHAR)
	// 	add_token(env, col, "LABEL_CHAR", ":");
	else if (line[*col] == SEPARATOR_CHAR)
		add_token(env, col, SEPARATOR_CHAR, ",");
	else if (line[*col] == DIRECT_CHAR)
		check_direct(env, line, col);//, quotation);
	else if (line[*col] == COMMENT_CHAR || line[*col] == ';')
		while (line[*col])
			*col = *col + 1;
	else
	{
		// while (line[*col + j] && line[*col + j] != LABEL_CHAR &&
		// line[*col + j] != SEPARATOR_CHAR && line[*col + j] != COMMENT_CHAR && 
		// line[*col + j] != DIRECT_CHAR && 
		// line[*col + j] != ' ' && line[*col + j] != '\t')
		while (line[*col + j] && ft_strchr(LABEL_CHARS, line[*col + j]))
			j++;
		if (line[*col + j] == LABEL_CHAR)
			check_label(env, line, col, j);
		else
			check_token(env, line, col, j);
	}
}

void		lexical_analyser(int fd, t_env *env)
{
	char	*line;
	int		i;
	int		quotation;

	quotation = 0;
	while(get_next_line(fd, &line) > 0)
	{
		i = 0;
		env->line = env->line + 1;
		if (!line[i] && quotation)
			env->last->value = ft_concat(env->last->value, "\n");
		// printf("[%d]	'%s'\n", env->line, line);
		while (line && line[i])
		{
			while(line[i] && !quotation && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i])
				generate_token(env, line, &i, &quotation);
			// if (line[i] == '.')
			// {
			// 	if (ft_strstr(line + i, NAME_CMD_STRING) || 
			// 	ft_strstr(line + i, COMMENT_CMD_STRING))
			// 		add_token(token, line + i)
			// }
			// i = i + ret;
		}
		free(line);
	}
}

void		init_env(t_env *env)
{
	env->line = 0;
	env->pc = 0;
	env->header = NULL;
	env->token = NULL;
	env->last = NULL;
	env->labels = NULL;
	env->inst = NULL;
	env->label_count = 0;
	// if (!(env->symbol = (t_symbol)malloc(sizeof(t_symbol))))
	// 	ft_exit("Malloc Error.");
	// init_symbol(env->symbol);
}

void		syntax_error(t_token *token)
{
	if (token)
		ft_printf("Syntax error at token [%d:%d] %d '%s'", 
		token->pos->line, token->pos->col, token->type, token->value);
	else
		ft_printf("Syntax error at END '(NULL)'");
	// free_env();
	ft_exit("");
}

t_token		*syntax_header(t_token *token)
{
	if (ft_strcmp(token->value, NAME_CMD_STRING))
		syntax_error(token);
	token = token->next;
	if (token->type != 32)//(ft_strcmp(token->type, "STRING"))
		syntax_error(token);
	token = token->next;
	if (ft_strcmp(token->value, COMMENT_CMD_STRING))
		syntax_error(token);
	token = token->next;
	if (token->type != 32)//(ft_strcmp(token->type, "STRING"))
		syntax_error(token);
	if (!token->next)
		syntax_error(NULL);
	return (token->next);
}


t_token		*syntax_instruction(t_token *token)
{
	int		line;

	if (token && token->type == T_LAB)//!ft_strcmp(token->type, "LABEL"))
		token = token->next;
	if (token && token->type == T_LAB)//!ft_strcmp(token->type, "LABEL"))
		return(token);
	if (!token || token->type != 16)//ft_strcmp(token->type, "OPCODE"))
		syntax_error(token);
	line = token->pos->line;
	token = token->next;
	// if (!token || (ft_strcmp(token->type, "TOKEN") && 
	// ft_strcmp(token->type, "DIRECT_LABEL") && ft_strcmp(token->type, "INDIRECT_LABEL")))
	if (!token || (token->type != T_REG && token->type != T_DIR
		 && token->type != T_IND))//(ft_strcmp(token->type, "REG") && !ft_strstr(token->type, "DIRECT")))
		syntax_error(token);
	token = token->next;
	while (token && token->pos->line == line)
	{
		if (!token || token->value[0] != SEPARATOR_CHAR ||
			 !token->next || token->next->pos->line != line)
			syntax_error(token);
		token = token->next;
		// if (!token || token->pos->line != line)
		// 	syntax_error(NULL);
		if (!token || (token->type != T_REG && token->type != T_DIR
			&& token->type != T_IND))//(ft_strcmp(token->type, "REG") && !ft_strstr(token->type, "DIRECT")))
			syntax_error(token);
		token = token->next;
	}
	// if (ft_strcmp(token->type, "STRING"))
	// 	syntax_error(token);
	// if (!token->next)
	// 	syntax_error(NULL);
	return (token);
}

// t_token		*syntax_analyser(t_token *token, t_env *env)
// {
// 	int		line;

// 	line = token->pos->line;
// 	while (token && token->pos->line == line)
// 	{
// 		while (token && !ft_strcmp(token->type, "LABEL"))
// 			add_label(token);
// 			// token = token->next;
// 	}
// 	return (token);
// }

void		init_label(t_env *env, t_token *token)
{
	t_label		*label;
	int			count;

	count = 0;
	while (token)
	{
		if (token->type == T_LAB)//(!ft_strcmp(token->type, "LABEL"))
			count++;
		token = token->next;
	}
	if (!(env->labels = (t_label **)malloc(sizeof(t_label) * count)))
		return ;
}

t_inst		*init_inst()
{
	t_inst		*inst;

	if (!(inst = (t_inst *)malloc(sizeof(t_inst))))
		return (NULL);
	inst->size = 0;
	inst->opcode = 0;
	inst->type = 0;
	inst->pcount = 0;
	inst->params = NULL;
	// inst->p1 = NULL;
	// inst->p2 = NULL;
	// inst->p3 = NULL;
	inst->next = NULL;
	return (inst);
}

void		add_label(t_token *token, t_env *env)
{
	t_label		*label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return ;
	label->name = token;
	label->addr = env->pc;
	env->labels[env->label_count] = label;
	env->label_count = env->label_count + 1;
}

void		add_inst(t_inst *inst, t_env *env)
{
	t_inst	*tmp;

	tmp = env->inst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		env->inst = inst;
	else
		tmp->next = inst;
}

void		type_byte(t_inst *inst, t_token *param, int pcount)
{
	unsigned char	type;
	int				bit;
	int				i;

	type = 0;
	bit = 1;
	i = 1;
	while (i++ < pcount)
		bit = bit + 2;
	if (param->type == T_REG)
		type = type | 1 << (8 - bit - 1);
	else if (param->type == T_DIR)
		type = type | 1 << (8 - bit);
	else if (param->type == T_IND)
		type = type | 1 << (8 - bit) | 1 << (8 - bit - 1);
	inst->type = inst->type | type;
	// ft_printf("Type : '%d', Bit : '%d'\n", type, bit);
}

void		ft_error(t_token *token, char *str)
{
	ft_printf("Syntax error at token [%d:%d] '%s' ", 
	token->pos->line, token->pos->col, token->value);
	// free_env();
	ft_exit(str);
}

void		check_ptype(t_inst *inst, t_op *op)
{
	char	ptypes[inst->pcount];
	char	tmp;
	t_token	*param;
	int		i;

	i = 0;
	param = inst->params;
	while (i < op->pcount)
	{
		tmp = 0;
		ptypes[i] = param->type;
		tmp = ptypes[i] | op->ptypes[i];
		if (tmp != op->ptypes[i])
			ft_error(param, "Parameter type not valid.");
		if (op->code_byte)
			type_byte(inst, param, i + 1);
		i++;
		if (i < op->pcount)
			param = param->next->next;
	}
}

void		check_pcount(t_token *start, t_token *end,
			 t_inst *inst, t_op *op)
{
	int		i;

	i = 0;
	while (i < op->pcount && start->next != end)
	{
		start = start->next;
		if (start->type == T_REG)//(!ft_strcmp(start->type, "REG"))
			inst->size = inst->size + 1;
		else if (start->type == T_IND)//(ft_strstr(start->type, "INDIRECT"))// ||
		//  !ft_strcmp(start->type, "DIRECT_LABEL"))
			inst->size = inst->size + 2;
		else
		{
			if (op->label_size)
				inst->size = inst->size + 2;
			else
				inst->size = inst->size + 4;
		}
		// inst->params[i] = start;
		i++;
		if (i < op->pcount && start->next != end)
			start = start->next;
	}
	if (start->next != end || i != op->pcount)
		ft_error(start, "Parameters count not matching.");
}

t_op		*get_op_by_name(char *str)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(str, op_tab[i].op))
			return (&op_tab[i]);
		i++;
	}
	return (NULL);
}

void		ft_add_inst(t_token *start, t_token *end, t_env *env)
{
	t_inst		*inst;
	t_op		*op;
	int			i;

	i = 0;
	inst = init_inst();
	op = NULL;
	// while (start != end)
	// {
	if (start->type == T_LAB)//(!ft_strcmp(start->type, "LABEL"))
	{
		add_label(start, env);
		// inst->label = env->labels[env->label_count - 1];
		// ft_printf("Label : '%s', Addr : '%d'\n", inst->label->name->value, inst->label->addr);
		start = start->next;
	}
	if (start == end)
		return ;
	if (start != end && start->type == 16)//!ft_strcmp(start->type, "OPCODE"))
	{
		op = get_op_by_name(start->value);
		inst->opcode = op->opcode;
		inst->size = inst->size + 1;
		if (op->code_byte)
			inst->size = inst->size + 1;
	}
	// count = op->pcount;
	// start = start->next;
	if (start->next != end)
		inst->params = start->next;
	inst->pcount = op->pcount;
	check_pcount(start, end, inst, op);
	check_ptype(inst, op);
	// while (i < op->pcount && start->next != end)
	// {
	// 	start = start->next;
	// 	if (!ft_strcmp(start->type, "REG"))
	// 		inst->size = inst->size + 1;
	// 	else if (ft_strstr(start->type, "INDIRECT"))// ||
	// 	//  !ft_strcmp(start->type, "DIRECT_LABEL"))
	// 		inst->size = inst->size + 2;
	// 	else
	// 	{
	// 		if (op->label_size)
	// 			inst->size = inst->size + 2;
	// 		else
	// 			inst->size = inst->size + 4;
	// 	}
	// 	// inst->params[i] = start;
	// 	i++;
	// 	if (i < op->count && start->next != end)
	// 		start = start->next;
	// }
	// if (start->next != end)
	// 	ft_exit("Parameters count not matching.");
	env->pc = env->pc + inst->size;
	add_inst(inst, env);
	// 	start = start->next;
	// }
}

void		syntax_analyser(t_env *env)
{
	t_token		*token;
	t_token		*end;
	t_inst		*inst;
	int			i;

	token = env->token;
	token = syntax_header(token);
	printf("token after header : '%s'", token->value);
	init_label(env, token);
	while (token)
	// {
	// 	if (!ft_strcmp(token->type, "TOKEN"))
	// 	{
	// 		i = 0;
	// 		// printf("OKK");
	// 		while (op_tab[i].opcode)
	// 		{
	// 			if (!ft_strcmp(token->value, op_tab[i].op))
	// 				ft_printf("OP: [%s:%d:%d,%d,%d]\n", op_tab[i].op, op_tab[i].opcode, op_tab[i].ptypes[0], op_tab[i].ptypes[1], op_tab[i].ptypes[2]);
	// 			i++;
	// 		}
	// 	}
	// 	token = token->next;
	// }
	{
		end = syntax_instruction(token);//, env);
		ft_add_inst(token,end, env);
		token = end;
	}
	// while (token)
	// {

	// }
}

int			main(int argc, char **argv)
{
	int			len;
	int			fd;
	t_env		env;

	if (argc != 2)
		return (0);
	len = ft_strlen(argv[1]);
	if (argv[1][len - 2] != '.' && argv[1][len - 1] != 's')
		ft_exit("Usage: ./asm <filename>.s");
	fd = open(argv[1], O_RDONLY);
	init_env(&env);
	lexical_analyser(fd, &env);
	print_tokens(&env);
	syntax_analyser(&env);
	print_inst(&env);
	print_labels(&env);
	ft_printf("PC : %d\n", env.pc);
	// print_tokens(&env);
	// ft_check_header(fd, &env);
	// ft_make_string(fd);
}
// int		main(int argc, char **argv)
// {
// 	int		len;
// 	int		fd;
// 	char	*str;
// 	int		size = 16;
// 	int 	i = 0;
// 	char	*file_name;

// 	if (argc != 2)
// 		return (0);
// 						printf("%s\n", argv[1]);
// 	len = ft_strlen(argv[1]);
// 						printf("%d\n", len);
// 	if (argv[1][len - 1] != 's' || argv[1][len - 2] != '.')
// 	{
// 		printf("Only '.s' file extension allowed.\n");
// 		return (0);
// 	}
// 	file_name = (char *)malloc(sizeof(char) * len + 3);
// 	ft_strncpy(file_name, argv[1], len - 1);
// 	ft_strcat(file_name, "cor");
// 	fd = open(argv[1], O_RDONLY);
// 	str = (char *)malloc(sizeof(char) * (size + 1));
// 	while (i < 16)
// 	{
// 		str[i] = i;
// 		i++;
// 	}
// 	printf("str = '%s'\n", str);
// 	fd = open(file_name, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
// 	printf("fd = %d\n", fd);
// 	write(fd, str, 16);
// 	write(fd, str, 16);
// 	// write(fd, "Hii", 3);
// 	// ft_putnstr_fd(str, 16, fd);


// 	char	*line;

// 	while (get_next_line(&line, fd) > 0)
// 	{
// 		if (line && *line)
// 		{
// 			while (*line)
// 			{
// 				while (*line && *line)
// 			}
// 		}
// 	}
// 	return (0);
// }
