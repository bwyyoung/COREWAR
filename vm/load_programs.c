/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_programs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:18:29 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/03 20:55:32 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Reads the program bytes from the file and writes them to the board.
** The board is already incremented by offset so that all the programs are
** evenly spaced on the board.
*/

void		write_program_to_board(t_env *env, t_player *player,
										int offset, int fd)
{
	uint8_t		c;
	int			read_return;
	uint32_t	champ_size;

	c = 0;
	champ_size = 0;
	while (0 < (read_return = read(fd, &c, 1)))
	{
		if (read_return == -1)
			ft_error_errno(NULL);
		env->board[offset % MEM_SIZE] = c;
		env->prog_num_board[offset % MEM_SIZE] = player->prog_num;
		offset++;
		champ_size++;
	}
	if (champ_size != player->size)
		ft_error("The player's size is different from"
					" the size defined in the header");
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

void		reader(t_env *e, t_player *player, char *arg)
{
	int			fd;
	uint32_t	magic;

	if (-1 == (fd = open(arg, O_RDONLY)))
		ft_error_errno(NULL);
	magic = 0;
	if (-1 == read(fd, &magic, sizeof(magic)))
		ft_error_errno(NULL);
	if (rev_endian(magic) != COREWAR_EXEC_MAGIC)
		error_exit(e, 4);
	if (-1 == read(fd, player->name, PROG_NAME_LENGTH))
		ft_error_errno(NULL);
	if (-1 == lseek(fd, 4, SEEK_CUR))
		ft_error_errno(NULL);
	if (-1 == read(fd, &player->size, sizeof(player->size)))
		ft_error_errno(NULL);
	if ((player->size = rev_endian(player->size)) > CHAMP_MAX_SIZE)
		ft_error("Champ is too large"); // use varargs?
	if (-1 == read(fd, player->comment, COMMENT_LENGTH))
		ft_error_errno(NULL);
	if (-1 == lseek(fd, 4, SEEK_CUR))
		ft_error_errno(NULL);
	write_program_to_board(e, player, e->offset, fd);
	if (-1 == close(fd))
		ft_error_errno(NULL);
}
