/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:49:06 by byoung-w          #+#    #+#             */
/*   Updated: 2017/09/08 14:49:10 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		clean_head(t_cursor *head)
{
	t_cursor *temp;

	while (head)
	{
		if (head->next)
		{
			temp = head;
			head = head->next;
			SAFE_DELETE(temp);
		}
		if (head->counter)
			SAFE_DELETE(head);
	}
}

/*
**	Example: ./corewar -visual -n -1 filename.cor
**	GUI: ./corewar -visual [Players]
**	Default Player Numbers: 1, 2, 3, 4...
**	Change Player Number: -n -1 filename.cor
**	Dump: ./corewar -dump 300 [Players](prints the memory after 300 cycles)
*/
void		print_instructions(void)
{
	ft_printf("Usage: ./corewar [-d N -s N -v N | -b --stealth "
		"| --visual --stealth] [-a] <champion1.cor> <...>\n");
	ft_printf("Example              : ./corewar --visual -n -1 filename.cor");
	ft_printf("\t-n: Specify Number of Players(-n -1 filename.cor)");
	ft_printf("-a        : Prints output from \"aff\" (Default is to hide it)");
	ft_printf("\n#### TEXT OUTPUT MODE #######################################"
		"###################\n");
	ft_printf("\t-d N   : Dumps memory after N cycles then exits\n");
	ft_printf("\t-s N   : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("\t-v N   : Verbosity levels, can be added together to enable "
		"several\n");
	ft_printf("\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t- 1 : Show lives\n");
	ft_printf("\t\t- 2 : Show cycles\n");
	ft_printf("\t\t- 4 : Show operations (Params are NOT literal ...)\n");
	ft_printf("\t\t- 8 : Show deaths\n");
	ft_printf("\t\t- 16 : Show PC movements (Except for jumps)\n");
	ft_printf("#### BINARY OUTPUT MODE ########################################"
		"################\n");
	ft_printf("-b        : Binary output mode for corewar\n");
	ft_printf("		--stealth : Hides the real contents of the memory\n");
	ft_printf("#### NCURSES OUTPUT MODE #######################################"
		"################\n");
	ft_printf("--visual  : Visual output mode\n");
	ft_printf("--stealth : Hides the real contents of the memory\n");
	ft_printf("################################################################"
		"################\n");
}


void		error_msg_2(int i)
{
	if (i == 11)
		ft_putstr_fd("\x1b[31m[Too few arguments for -dump]\x1b[0m ", 2);
	else if (i == 12)
		ft_putstr_fd("\x1b[31m[-dump value is larger than int max]\x1b[0m ", 2);
	else if (i == 13)
		ft_putstr_fd("\x1b[31m[Too few arguments for -n flag]\x1b[0m ", 2);
	else if (i == 14)
		ft_putstr_fd("\x1b[31m[Non numerical chars in numb input]\x1b[0m ", 2);
	else if (i == 15)
		ft_putstr_fd("\x1b[31m[Wrong int value for -n flag.]\x1b[0m ", 2);
	else if (i == 16)
		ft_putstr_fd("\x1b[31m[Wrong file type. Usage: .cor]\x1b[0m ", 2);
	else if (i == 17)
		ft_putstr_fd("\x1b[31m[The file size is too large.]\x1b[0m ", 2);
	else if (i == 18)
		ft_putstr_fd("\x1b[31m[Too few arguments for -bonus flag]\x1b[0m ", 2);
	else if (i == 19)
		ft_putstr_fd("\x1b[31m[Wrong int value for -dump flag]\x1b[0m ", 2);
	else if (i == 20)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m ", 2);
	else
		ft_putstr_fd("\x1b[31m[ERROR]\x1b[0m ", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void		error_msg(int i)
{
	if (i == 1)
		ft_putstr_fd("\x1b[31m[Failed to open]\x1b[0m ", 2);
	else if (i == 2)
		ft_putstr_fd("\x1b[31m[Failed to read file]\x1b[0m ", 2);
	else if (i == 3)
		ft_putstr_fd("\x1b[31m[Failed to close file]\x1b[0m ", 2);
	else if (i == 4)
		ft_putstr_fd("\x1b[31m[Wrong Corewar Exec Magic]\x1b[0m ", 2);
	else if (i == 5)
		ft_putstr_fd("\x1b[31m[Incorrect Name Chars]\x1b[0m ", 2);
	else if (i == 6)
		ft_putstr_fd("\x1b[31m[Player size too big]\x1b[0m ", 2);
	else if (i == 7)
		ft_putstr_fd("\x1b[31m[Wrong int value]\x1b[0m ", 2);
	else if (i == 8)
		ft_putstr_fd("\x1b[31m[Too many players]\x1b[0m ", 2);
	else if (i == 9)
		ft_putstr_fd("\x1b[31m[Duplicate player number]\x1b[0m ", 2);
	else if (i == 10)
		ft_putstr_fd("\x1b[31m[Incorrect comment chars]\x1b[0m ", 2);
	else
		ft_putstr_fd("\x1b[31m[ERROR]\x1b[0m ", 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void		error_exit(t_env *e, int i)
{
	if (e->head)
		clean_head(e->head);
	if (i > 0 && i < 11)
		error_msg(i);
	else if (i > 10)
		error_msg_2(i);
	else
	{
		ft_putstr_fd("\x1b[31m[Unknown Error Message: ]\x1b[0m ", 2);
		ft_printf("Code %i\n", i);
		exit(1);
	}
}
