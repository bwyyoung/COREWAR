/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_programs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:18:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/10/24 18:30:43 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Reads the program bytes from the file and writes them to the board.
** The board is already incremented by offset so that all the programs are
** evenly spaced on the board.
*/
void	write_program_to_board(uint8_t *board, int offset, int fd)
{
	uint8_t	c;
	int		read_return;

	c = 0;
	while (0 < (read_return = read(fd, &c, 1)))
	{
		if (read_return == -1)
			ft_error_errno(NULL);
		board[offset++ % MEM_SIZE] = c;
	}
}

/*
** Switches the endian of the num.
** Example:
**		The magic bytes are stored in the file as f383ea
**		but in the header file the magic num is stored as
**		ea83f3. Therefore we need to reverse the board value
**		before comparing it to the header value.
*/
uint32_t	rev_endian(uint32_t num)
{
	return (((num << 24))
			| ((num << 8) & 0x00ff0000)
			| ((num >> 8) & 0x0000ff00)
			| ((num >> 24)));
}

/*
** Reads the .cor file given as argument.
** The file is invalid if it doesn't have the COREWAR_EXEC_MAGIC
** at the start of it.
*/
void	reader(t_env *e, int offset, char *arg)
{
	int			fd;
	uint32_t	magic;

	magic = 0;
	if (-1 == (fd = open(arg, O_RDONLY)))
		error_exit(e, 1);
	if (-1 == read(fd, &magic, 4))
		error_exit(e, 4);
	magic = rev_endian(magic);
	if (magic != COREWAR_EXEC_MAGIC)
		error_exit(e, 4);
	if (-1 == lseek(fd, sizeof(uint32_t), 0))
		error_exit(e, 4);
	if (-1 == read(fd, e->new_player->name, PROG_NAME_LENGTH))
		ft_error_errno(NULL);
	if (-1 == lseek(fd, sizeof(t_header), 0))
		ft_error_errno(NULL);
	write_program_to_board(e->board, offset, fd);
	if (-1 == close(fd))
		ft_error_errno(NULL);
}

/*
** Adds a player to the list of players.
*/
void	add_player_list(t_env *env, t_player *new_player)
{
	t_list *new_node;

	if (!(new_node = ft_lstnew(new_player, sizeof(t_player))))
		ft_error_errno(NULL);
	if (!env->players)
		env->players = new_node;
	else
	{
		env->element = env->players;
		ft_lstadd(&env->players, new_node);
	}
}
