/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <ppatel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 15:28:47 by ppatel            #+#    #+#             */
/*   Updated: 2017/10/23 17:03:19 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../includes/op.h"
#include "../includes/asm.h"

t_token		*create_token(t_env *env, int *col, char type, char *value)
{
	t_token		*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	if (!(token->pos = (t_location *)malloc(sizeof(t_location))))
		return (NULL);
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

void		get_filename(t_env *env, char *name)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(name) + 3)))
		ft_exit("Malloc Error.");
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
	if (argc >= 2)
		while (i < argc)
		{
			len = ft_strlen(argv[i]);
			if (len < 3 || (argv[i][len - 2] != '.' && argv[i][len - 1] != 's'))
				ft_exit("Usage: ./asm <filename.s>");
			if ((fd = open(argv[i], O_RDONLY)) < 0)
				ft_exit(strerror(errno));
			init_env(&env);
			lexical_analyser(fd, &env);
			close(fd);
			syntax_analyser(&env);
			get_filename(&env, argv[i++]);
			ft_write_hex(&env);
			free_env(&env);
		}
	else
		ft_exit("Usage: ./asm <filename.s>");
	return (0);
}
