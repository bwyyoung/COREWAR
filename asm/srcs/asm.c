/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:47:13 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/18 12:13:43 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../includes/op.h"
#include "../includes/asm.h"

// void	print_tokens(t_env *env)
// {
// 	t_token		*token;

// 	token = env->token;
// 	while (token)
// 	{
// 		ft_printf("[line:col] = [%d:%d], Type : '%d', Value : '%s'\n", 
// 		token->pos->line, token->pos->col, token->type, token->value);
// 		token = token->next;
// 	}
// }

// void	print_labels(t_env *env)
// {
// 	t_label		*label;
// 	int			i = 0;

// 	while (i < env->label_count)
// 	{
// 		label = env->labels[i];
// 		ft_printf("[line:col] = [%d:%d], LABEL : '%s', Addr : '%d'\n", 
// 		label->name->pos->line, label->name->pos->col, label->name->value, label->addr);
// 		i++;
// 	}
// }

// void	print_inst(t_env *env)
// {
// 	t_inst		*inst;
// 	int			i = 0;

// 	inst = env->inst;
// 	while (inst)
// 	{
// 		ft_printf("%d\n", i++);
// 		ft_printf("OPCODE = '%d', Type : '%d', size : '%d', pcount : '%d', params : '%s', line[%d:%d]\n", 
// 		inst->opcode, inst->type, inst->size, inst->pcount, inst->params->value, inst->params->pos->line, inst->params->pos->col);
// 		inst = inst->next;
// 	}
// }

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

t_token		*create_token(t_env *env, int *col, char type, char *value)
{
	t_token		*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return NULL;
	if	(!(token->pos = (t_location *)malloc(sizeof(t_location))))
		return NULL;
	token->pos->line = env->line;
	token->pos->col = *col + 1;
	token->type = type;
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

void		check_command(t_env *env, char *line, int *col)
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
	*col = *quotation == 0 ? *col + 1 : *col;
	while (line[*col + j] && line[*col + j] != '"')
		j++;
	str = ft_strndup(line + *col, j);
	if (*quotation == 1)
	{
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
	free(str);
}

void		check_direct(t_env *env, char *line, int *col)
{
	int		j;
	char	*str;

	j = 1;
	*col = *col + 1;
	if (line[*col] == LABEL_CHAR && ft_strchr(LABEL_CHARS, line[*col + 1]))
	{
		while (line[*col + j] && ft_strchr(LABEL_CHARS, line[*col + j]))
			j++;
	}
	else if ((line[*col] == '-' && ft_isdigit(line[*col + 1])) ||
	 ft_isdigit(line[*col]))
	{
		j = line[*col] == '-' ? 1 : 0;
		while (line[*col + j] && ft_isdigit(line[*col + j]))
			j++;
	}
	else
	{
		ft_printf("Lexical error at [%d:%d].", env->line, *col);
		ft_exit("");
	}
	str = ft_strndup(line + *col, j);
	add_token(env, col, T_DIR, str);
	free(str);
}

void		check_label(t_env *env, char *line, int *col, int j)
{
	char	*str;

	if (j == 0)
	{
		while (ft_strchr(LABEL_CHARS, line[*col + j + 1]))
			j++;
		if (j == 0)
		{
			ft_printf("Lexical error at [%d:%d].", env->line, *col + 1);
			ft_exit("");
		}
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
	int			nb;
	size_t		i;

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
		else
		{
			ft_printf("Lexical error at [%d:%d].", env->line, *col + 1);
			ft_exit("");
		}
	}
	else if (i == ft_strlen(str))
		add_token(env, col, T_IND, str);
	else
		add_token(env, col, 0, str);
}

void		check_token(t_env *env, char *line, int *col, int j)
{
	char	*str;

	str = NULL;
	if (j != 0)
	{
		str = ft_strndup(line + *col, j);
		check_op_reg(env, col, str);
	}
	else if (j == 0 && line[*col] == '-' && ft_isdigit(line[*col + 1]))
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
	else if (line[*col] == '.')
		check_command(env, line, col);
	else if (line[*col] == SEPARATOR_CHAR)
		add_token(env, col, SEPARATOR_CHAR, ",");
	else if (line[*col] == DIRECT_CHAR)
		check_direct(env, line, col);
	else if (line[*col] == COMMENT_CHAR || line[*col] == ';')
		while (line[*col])
			*col = *col + 1;
	else
	{
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
		while (line && line[i])
		{
			while(line[i] && !quotation && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i])
				generate_token(env, line, &i, &quotation);
		}
		free(line);
	}
}

void		free_tokens(t_token *token)
{
	t_token		*tmp;

	while (token)
	{
		free(token->pos);
		free(token->value);
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

void		free_labels(t_label **labels, int count)
{
	int		i;

	i = 0;
	while (i < count)
		free(labels[i++]);
	free(labels);
}

void		free_inst(t_inst *inst)
{
	t_inst	*tmp;

	while (inst)
	{
		tmp = inst->next;
		free(inst);
		inst = tmp;
	}
}

void		free_env(t_env *env)
{
	if (env->header)
		free(env->header);
	if (env->token)
		free_tokens(env->token);
	if	(env->labels)
		free_labels(env->labels, env->label_count);
	if (env->inst)
		free_inst(env->inst);
	if (env->str)
		free(env->str);
	if (env->filename)
		free(env->filename);
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
	env->str = NULL;
	env->filename = NULL;
	env->label_count = 0;
}

void		syntax_error(t_token *token, t_env *env)
{
	if (token)
		ft_printf("Syntax error at token [%d:%d] %d '%s'", 
		token->pos->line, token->pos->col, token->type, token->value);
	else
		ft_printf("Syntax error at END '(NULL)'");
	free_env(env);
	ft_exit("");
}

t_token		*syntax_header(t_token *token, t_env *env)
{
	if (ft_strcmp(token->value, NAME_CMD_STRING))
		syntax_error(token, env);
	token = token->next;
	if (token->type != 32)
		syntax_error(token, env);
	token = token->next;
	if (ft_strcmp(token->value, COMMENT_CMD_STRING))
		syntax_error(token, env);
	token = token->next;
	if (token->type != 32)
		syntax_error(token, env);
	if (!token->next)
		syntax_error(NULL, env);
	return (token->next);
}


t_token		*syntax_instruction(t_token *token, t_env *env)
{
	int		line;

	token = token->type == T_LAB ? token->next : token;
	if (!token || (token && token->type == T_LAB))
		return(token);
	if (!token || token->type != 16)
		syntax_error(token, env);
	line = token->pos->line;
	token = token->next;
	if (!token || (token->type != T_REG && token->type != T_DIR
		 && token->type != T_IND))
		syntax_error(token, env);
	token = token->next;
	while (token && token->pos->line == line)
	{
		if (!token || token->value[0] != SEPARATOR_CHAR ||
			 !token->next || token->next->pos->line != line)
			syntax_error(token, env);
		token = token->next;
		if (!token || (token->type != T_REG && token->type != T_DIR &&
			 token->type != T_IND))
			syntax_error(token, env);
		token = token->next;
	}
	return (token);
}

void		init_label(t_env *env, t_token *token)
{
	int			count;

	count = 0;
	while (token)
	{
		if (token->type == T_LAB)
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
	inst->next = NULL;
	return (inst);
}

t_token		*add_label(t_token *token, t_env *env)
{
	t_label		*label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	label->name = token;
	label->addr = env->pc;
	env->labels[env->label_count] = label;
	env->label_count = env->label_count + 1;
	return (token->next);
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
}

void		ft_error(t_token *token, t_env *env, char *str)
{
	ft_printf("Syntax error at token [%d:%d] '%s' ", 
	token->pos->line, token->pos->col, token->value);
	free_env(env);
	ft_exit(str);
}

void		check_ptype(t_inst *inst, t_op *op, t_env *env)
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
			ft_error(param, env, "Parameter type not valid.");
		if (op->code_byte)
			type_byte(inst, param, i + 1);
		i++;
		if (i < op->pcount)
			param = param->next->next;
	}
}

void		check_pcount(t_token *start, t_token *end, t_inst *inst, t_env *env)
{
	int		i;

	i = 0;
	while (i < inst->pcount && start->next != end)
	{
		start = start->next;
		if (start->type == T_REG)
			inst->size = inst->size + 1;
		else if (start->type == T_IND)
			inst->size = inst->size + 2;
		else
		{
			if (inst->type)
				inst->size = inst->size + 2;
			else
				inst->size = inst->size + 4;
		}
		i++;
		if (i < inst->pcount && start->next != end)
			start = start->next;
	}
	inst->type = 0;
	if (start->next != end || i != inst->pcount)
		ft_error(start, env, "Parameters count not matching.");
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
	op = NULL;
	if (start->type == T_LAB)
		start = add_label(start, env);
	if (start == end)
		return ;
	inst = init_inst();
	if (start != end && start->type == 16)
	{
		op = get_op_by_name(start->value);
		inst->opcode = op->opcode;
		inst->size = op->code_byte ? inst->size + 2 : inst->size + 1;
	}
	if (start->next != end)
		inst->params = start->next;
	inst->pcount = op->pcount;
	inst->type = op->label_size ? 1 : 0;
	check_pcount(start, end, inst, env);
	check_ptype(inst, op, env);
	env->pc = env->pc + inst->size;
	add_inst(inst, env);
}

void		syntax_analyser(t_env *env)
{
	t_token		*token;
	t_token		*end;

	token = env->token;
	token = syntax_header(token, env);
	init_label(env, token);
	while (token)
	{
		end = syntax_instruction(token, env);
		ft_add_inst(token,end, env);
		token = end;
	}
}

void		reverse_bytes(char *str, int start, int n)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = n - 1;
	while (i < n / 2)
	{
		tmp = str[start + i];
		str[start + i] = str[start + j];
		str[start + j] = tmp;
		i++;
		j--;
	}
}

void		add_ind(t_env *env, t_token *param, int start)
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

void		add_dir(t_env *env, t_inst *inst, t_token *param, int start)
{
	int			i;
	int			size;
	uint32_t	dir;

	i = 0;
	dir = 0;
	size = op_tab[inst->opcode - 1].label_size ? 2 : 4;
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

void		ft_add_inst_bytes(t_env *env, t_inst *inst, int start)
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

void		ft_write_hex(t_env *env)
{
	t_inst	*inst;
	char	*str;
	int		fd;

	inst = env->inst;
	if (!(str = (char *)malloc(sizeof(char) * env->pc + 1)))
		ft_exit("");
	env->pc = 0;
	env->str = str;
	while (inst)
	{
		ft_add_inst_bytes(env, inst, env->pc);
		inst = inst->next;
	}
	fd = open(env->filename, O_WRONLY | O_TRUNC | O_CREAT,
		 S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	write(fd, env->header, sizeof(header_t));
	write(fd, str, env->pc);
	close(fd);
}

void		fill_header(t_env *env)
{
	header_t	*header;
	t_token		*str;

	if (!(header = (header_t *)malloc(sizeof(header_t))))
		ft_exit("");
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

void		get_filename(t_env *env, char *name)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(name) + 3)))
		ft_exit("");
	ft_strcpy(str, name);
	str[ft_strlen(name) - 1] = '\0';
	ft_strcat(str, "cor");
	env->filename = str;
}

int			main(int argc, char **argv)
{
	int			len;
	int			fd;
	t_env		env;
	int			i;

	i = 1;
	if (argc != 2)
		return (0);
	while (i < argc)
	{
		len = ft_strlen(argv[i]);
		if (len < 3 || (argv[i][len - 2] != '.' && argv[i][len - 1] != 's'))
			ft_exit("Usage: ./asm <filename>.s");
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			ft_exit("Error opening the file.");
		init_env(&env);
		lexical_analyser(fd, &env);
				// print_tokens(&env);
		close(fd);
		syntax_analyser(&env);
		get_filename(&env, argv[i]);
		fill_header(&env);
				// print_inst(&env);
				// print_labels(&env);
				// ft_printf("PC : %d\n", env.pc);
		ft_write_hex(&env);
		ft_printf("Writing output program to %s\n", env.filename);
		free_env(&env);
		i++;
	}
}
