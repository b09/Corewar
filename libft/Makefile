# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/29 17:19:55 by bprado        #+#    #+#                  #
#    Updated: 2020/06/19 18:35:43 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= 	libft.a

FLAGS=	-Wall -Wextra -Werror -02

SRC=	$(wildcard src/*.c)

OBJ=	$(patsubst src/%.c,obj/%.o,$(SRC))

CC=		gcc

# Colors
PURPLE = \033[95m
CYAN = \033[96m
DARKCYAN = \033[36m
BLUE = \033[94m
GREEN = \033[92m
YELLOW = \033[93m
RED = \033[91m
BOLD = \033[1m
# UNDERLINE = \033[4m
END = \033[0m

# tput commands
BOLD := `tput bold`
UNDERLINE := `tput smul`
END_TPUT := `tput sgr0`

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))


all: $(NAME)

# begin_statement:
# 	@printf "$(BOLD) *** Compiling $(NAME) ***$(END_TPUT)\n"

# $(NAME): begin_statement $(OBJ)
$(NAME): $(OBJ)
	@printf " -- libft obj files done. --\n"
	@ar rcs $(NAME) $(OBJ)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/libft.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for \
	$(PURPLE)$(current_dir)/$<$(END)\n"
	@$(CC) -o $@ -c $< $(CFLAGS) -I inc -I .

clean:
	@printf "Cleaning$(BOLD)   libft object files$(END_TPUT)\n"
	@rm -rf obj

fclean: clean
	@printf "Deleting$(YELLOW)$(BOLD)   $(NAME)$(END)$(END_TPUT)\n"
	@rm -rf $(NAME)

re: fclean all
