# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mda-cost <mda-cost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:21:23 by mda-cost          #+#    #+#              #
#    Updated: 2017/11/11 17:18:23 by dengstra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ../corewar

CC		= gcc

CFLAGS	= -g -Wextra -Wall -Werror -D_XOPEN_SOURCE_EXTENDED

RM		= rm -rf

LIB			=	libft
OBJS		=	objs
SRCS		=	.
INCS		=	.
SHELL		=	/bin/bash
SOUND		=	../sound
INCLUDES	=	-I$(INCS) -I$(LIB) -I $(SOUND)
LIBS		=	-L $(LIB) -lft -lncurses /Users/$(USER)/.brew/opt/libsndfile/lib/libsndfile.1.dylib
LINK		=	-L $(SOUND) -lcommon -L $(SOUND) -lportaudio -L $(SOUND) -lsndfile
FRAMEWORK	=	-framework CoreServices -framework CoreFoundation \
				-framework AudioUnit -framework AudioToolbox -framework CoreAudio

# headers files
I_FILES 	=	cutscene.h \
				matrix.h \
				mgr_graphics.h \
				op.h \
				vm.h
I_SRCS		=	$(addprefix $(INCS)/,$(I_FILES))

# source files
C_FILES		=	main.c \
				run_game.c \
				env.c \
				load_programs.c \
				creator.c regs.c ft_error.c \
				kill_processes.c dump_memory.c executor.c\
				param_vals.c board_vals.c \
				op_utility.c op_get_sizes.c op_arithmetic.c op_store.c op_load.c \
				op_zjmp.c op_live.c op_bitwise.c op_fork.c op.c op_aff.c \
				op_index_store.c \
				op_index_load.c \
				parse_flags.c \
				error.c \
				parse_flags_calc.c \
				list_players.c \
				list_process.c \
				mgr_graphics.c \
				mgr_input.c \
				mgr_time.c \
				print_verbosity_sixteen.c \
				vprint.c \
				mgr_graphics_board.c \
				mgr_graphics_log.c \
				mgr_graphics_player.c \
				mgr_graphics_process.c \
				mgr_graphics_stats.c \
				load_players.c \
				printer.c \
				matrix.c \
				cutscene.c \
				cutscene_sound.c \
				cutscene_sound_load.c \
				cutscene_sound_play.c \
				mgr_graphics_loop.c \
				cutscene_sound_music.c \
				cutscene_video_load.c \
				cutscene_video_play.c \
				cutscene_dialog_load.c \
				cutscene_dialog_play.c \
				cutscene_gameover.c \
				cutscene_gameover_pill.c

C_SRCS		=	$(addprefix $(SRCS)/,$(C_FILES))

# object files
O_FILES		=	$(C_FILES:.c=.o)
O_SRCS		=	$(addprefix $(OBJS)/,$(O_FILES))

# Print
ACTUAL		= $(words $(COUNT))
TOTAL		= $(words $(filter %.c,$(C_SRCS)))
INCREMENT	= $(eval COUNT+=1)

PRINTINC	= $(INCREMENT) $(PRINT)
PRINT		= printf "\r $(REDB)%3s%%$(NC)\t -->>\t$(REDB)%-60s$(NC)\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$@"
PRINTDONE	= printf "\r $(GREENB)%3s%%$(NC)\t -->>\t$(GREENB)%-60s$(NC)\r" "$(shell echo $(ACTUAL)\*100\/$(TOTAL) | bc)" "$@"

# colors
REDB=\033[31;1m
GREENB=\033[32;1m
NC=\033[0m

all: $(NAME)

$(NAME): $(O_SRCS)
	@make -C $(LIB)
	@$(CC) $(C_FLAGS) $(LIBS) $(LINK) $(FRAMEWORK) $^ -o $@ && $(PRINTDONE) && echo

$(OBJS)/%.o: $(SRCS)/%.c $(I_SRCS)
	@mkdir -p $(OBJS)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@ && $(PRINTINC)

.PHONY: all clean fclean re

clean:
	@make clean -C $(LIB)
	@rm -rf $(O_FILES) $(OBJS)

fclean: clean
	@make fclean -C $(LIB)
	@rm -f $(NAME)

re: fclean all

