/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_programs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:18:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/12 14:57:03 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	read_program(uint8_t *board, int fd)
{
	uint8_t c;

	while (0 < read(fd, &c, 1))
		*board++ = c;
}

static void	reader(uint8_t *board, t_player *player, int offset, char *arg)
{
	int		fd;

	fd = open(arg, O_RDONLY);
	lseek(fd, sizeof(uint32_t), 0);
	read(fd, player->name, 128);
	lseek(fd, sizeof(t_header), 0);
	read_program(&board[offset], fd);
	close(fd);
}

void		load_programs(t_env *env, char *argv[])
{
	uint8_t			*board;
	int				offset;
	t_player		*player;
	uint32_t		prog_num;

	board = env->board;
	offset = 0;
	prog_num = 0xffffffff;
	if (env->options[d] == 1)
		argv += 2;
	while (*argv)
	{
		player = create_player(prog_num);
		reader(board, player, offset, *argv);
		add_process(env, create_process(offset, prog_num, player->name));
		ft_lstadd(&env->players, ft_lstnew(player, sizeof(t_player)));
		offset += MEM_SIZE / (env->num_players);
		argv++;
		prog_num--;
	}
}
