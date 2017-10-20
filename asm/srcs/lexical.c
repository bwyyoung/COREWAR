/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:53:46 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/20 12:58:15 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

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
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		env->line = env->line + 1;
		if (!line[i] && quotation)
			env->last->value = ft_concat(env->last->value, "\n");
		while (line && line[i])
		{
			while (line[i] && !quotation && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i])
				generate_token(env, line, &i, &quotation);
		}
		free(line);
	}
}
