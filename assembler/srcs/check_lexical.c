/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:48:23 by ppatel            #+#    #+#             */
/*   Updated: 2017/11/11 22:13:22 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"

void		check_command(t_env *env, char *line, int *col)
{
	if (ft_strstr(line + *col, NAME_CMD_STRING))
		add_token(env, col, '.', NAME_CMD_STRING);
	else if (ft_strstr(line + *col, COMMENT_CMD_STRING))
		add_token(env, col, '.', COMMENT_CMD_STRING);
	else
	{
		ft_printf("Lexical error at [%d:%d]", env->line, *col + 1);
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
		ft_printf("Lexical error at [%d:%d]", env->line, *col);
		ft_exit("");
	}
	str = ft_strndup(line + *col, j);
	add_token(env, col, T_DIR, str);
	free(str);
}

void		check_label(t_env *env, char *line, int *col, int j)
{
	char	*str;

	str = NULL;
	if (j == 0)
	{
		while (ft_strchr(LABEL_CHARS, line[*col + j + 1]))
			j++;
		if (j == 0)
		{
			ft_printf("Lexical error at [%d:%d]", env->line, *col + 1);
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
