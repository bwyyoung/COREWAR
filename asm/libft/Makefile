# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppatel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/22 12:35:39 by ppatel            #+#    #+#              #
#    Updated: 2017/08/22 12:35:46 by ppatel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wall \
		-Wextra \
		-Werror \

NAME = libft.a

SDIR = .

SDIRPF = ft_printf

ODIR = objects

SRCS = $(SDIR)/ft_atoi.c \
	   $(SDIR)/ft_bzero.c \
	   $(SDIR)/ft_isalnum.c \
	   $(SDIR)/ft_isalpha.c \
	   $(SDIR)/ft_isascii.c \
	   $(SDIR)/ft_isdigit.c \
	   $(SDIR)/ft_isprint.c \
	   $(SDIR)/ft_itoa.c \
	   $(SDIR)/ft_lstadd.c \
	   $(SDIR)/ft_lstdel.c \
	   $(SDIR)/ft_lstdelone.c \
	   $(SDIR)/ft_lstiter.c \
	   $(SDIR)/ft_lstmap.c \
	   $(SDIR)/ft_lstnew.c \
	   $(SDIR)/ft_lstsize.c \
	   $(SDIR)/ft_memalloc.c \
	   $(SDIR)/ft_memccpy.c \
	   $(SDIR)/ft_memchr.c \
	   $(SDIR)/ft_memcmp.c \
	   $(SDIR)/ft_memcpy.c \
	   $(SDIR)/ft_memdel.c \
	   $(SDIR)/ft_memmove.c \
	   $(SDIR)/ft_memset.c \
	   $(SDIR)/ft_min.c \
	   $(SDIR)/ft_max.c \
	   $(SDIR)/ft_putchar.c \
	   $(SDIR)/ft_putchar_fd.c \
	   $(SDIR)/ft_putwchar.c \
	   $(SDIR)/ft_putwchar_fd.c \
	   $(SDIR)/ft_putendl.c \
	   $(SDIR)/ft_putendl_fd.c \
	   $(SDIR)/ft_putnbr.c \
	   $(SDIR)/ft_putnbr_fd.c \
	   $(SDIR)/ft_putnbrbase.c \
	   $(SDIR)/ft_putnbrbase_fd.c \
	   $(SDIR)/ft_putstr.c \
	   $(SDIR)/ft_putstr_fd.c \
	   $(SDIR)/ft_putnstr.c \
	   $(SDIR)/ft_putnstr_fd.c \
	   $(SDIR)/ft_putwstr.c \
	   $(SDIR)/ft_putwstr_fd.c \
	   $(SDIR)/ft_putnwstr.c \
	   $(SDIR)/ft_putnwstr_fd.c \
	   $(SDIR)/ft_sort_wordtab.c \
	   $(SDIR)/ft_split_whitespaces.c \
	   $(SDIR)/ft_strcat.c \
	   $(SDIR)/ft_strchr.c \
	   $(SDIR)/ft_strclen.c \
	   $(SDIR)/ft_strclr.c \
	   $(SDIR)/ft_strcmp.c \
	   $(SDIR)/ft_strcpy.c \
	   $(SDIR)/ft_strdel.c \
	   $(SDIR)/ft_strdup.c \
	   $(SDIR)/ft_strequ.c \
	   $(SDIR)/ft_striter.c \
	   $(SDIR)/ft_striteri.c \
	   $(SDIR)/ft_strjoin.c \
	   $(SDIR)/ft_strlcat.c \
	   $(SDIR)/ft_strlen.c \
	   $(SDIR)/ft_strnlen.c \
	   $(SDIR)/ft_strltrim.c \
	   $(SDIR)/ft_strmap.c \
	   $(SDIR)/ft_strmapi.c \
	   $(SDIR)/ft_strncat.c \
	   $(SDIR)/ft_strncmp.c \
	   $(SDIR)/ft_strncpy.c \
	   $(SDIR)/ft_strnequ.c \
	   $(SDIR)/ft_strnew.c \
	   $(SDIR)/ft_strnstr.c \
	   $(SDIR)/ft_strparts.c \
	   $(SDIR)/ft_strrchr.c \
	   $(SDIR)/ft_strsplit.c \
	   $(SDIR)/ft_strstr.c \
	   $(SDIR)/ft_strsub.c \
	   $(SDIR)/ft_strtrim.c \
	   $(SDIR)/ft_tolower.c \
	   $(SDIR)/ft_toupper.c \
	   $(SDIR)/get_next_line.c

PFSRCS = $(SDIRPF)/ft_printf.c \
		 $(SDIRPF)/ft_check_flags.c \
		 $(SDIRPF)/ft_check_specifier.c \
		 $(SDIRPF)/ft_tools.c \
		 $(SDIRPF)/ft_specifier_s.c \
		 $(SDIRPF)/ft_specifier_ws.c \
		 $(SDIRPF)/ft_specifier_c.c \
		 $(SDIRPF)/ft_specifier_wc.c \
		 $(SDIRPF)/ft_specifier_d.c \
		 $(SDIRPF)/ft_specifier_x.c \
		 $(SDIRPF)/ft_specifier_u.c \
		 $(SDIRPF)/ft_specifier_o.c \
		 $(SDIRPF)/ft_specifier_p.c \
		 $(SDIRPF)/ft_specifier_long.c \
		 $(SDIRPF)/ft_specifier_n.c \
		 $(SDIRPF)/ft_specifier_b.c \
		 $(SDIRPF)/ft_specifier_fd.c \
		 $(SDIRPF)/ft_specifier_f.c \
		 $(SDIRPF)/ft_specifier_unknown.c


OBJ = $(SRCS:$(SDIR)/%.c=$(ODIR)/%.o)

PFOBJ = $(PFSRCS:$(SDIRPF)/%.c=$(ODIR)/%.o)

HDRS =  -I./get_next_line.h \
		-I./libft.h \
		-I./ft_printf.h

all: $(NAME)

$(NAME): $(ODIR) $(OBJ) $(PFOBJ)
	@ar rc $@ $(OBJ) $(PFOBJ)
	@echo "Lib created."

$(ODIR):
	@echo "Wait \c"
	@mkdir $@

$(ODIR)/%.o: $(SDIR)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@

$(ODIR)/%.o: $(SDIRPF)/%.c
	@$(CC) $(FLAGS) -c $< $(HDRS) -o $@

clean:
	@rm -rf $(ODIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
