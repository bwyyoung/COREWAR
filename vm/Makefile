# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/06 18:30:14 by douglas           #+#    #+#              #
#    Updated: 2017/10/26 16:22:26 by dengstra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vm
FLAGS = -g -Wextra -Wall -Werror
#FLAGS =
LIBFT = ./libft
LIB = libft/libft.a -lcurses

SRC = main.c run_game.c \
		load_programs.c \
		creator.c regs.c ft_error.c \
		kill_processes.c add_process.c dump_memory.c executor.c\
		param_vals.c board_vals.c \
		op_utility.c op_get_sizes.c op_arithmetic.c op_store.c op_load.c \
		op_zjmp.c op_live.c op_bitwise.c op_fork.c op.c op_aff.c \
		parse_flags.c	\
		error.c			\
		parse_flags_calc.c \
		list_players.c		\
		list_process.c		\
		mgr_graphics.c		\
		mgr_input.c			\
		mgr_time.c			\
		print_verbosity_sixteen.c \
		vprint.c				\
		mgr_graphics_board.c	\
		mgr_graphics_log.c		\
		mgr_graphics_player.c	\
		mgr_graphics_process.c	\
		mgr_graphics_stats.c	\
		matrix.c


SRCO = ${SRC:%.c=%.o}

all: MAKE_LIBS $(NAME)

MAKE_LIBS		:
	@make -C libft/

$(NAME): $(SRCO)
	@gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

$(LIB):
	@make -C $(LIBFT)

clean:
	@/bin/rm -f $(SRCO)
	@make clean -C $(LIBFT)

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean re all make_lib
