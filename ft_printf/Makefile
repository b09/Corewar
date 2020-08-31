# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/03 16:52:44 by bprado        #+#    #+#                  #
#    Updated: 2020/07/01 13:59:02 by bprado        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a

# CFLAGS	= -Wall -Wextra -Werror -g
CFLAGS	= -g

SRC 	= $(wildcard src/*.c)

LIB 	= ../libft

INC 	= -I inc -I ../libft/inc

OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))

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

$(NAME): $(OBJ) ../libft/libft.a
	@echo "compiling ..."
	@cp ../libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/ft_printf.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for \
	$(PURPLE)$(current_dir)/$<$(END)\n"
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

../libft/libft.a: $(wildcard libft/*.c)
	@$(MAKE) -C $(LIB)

clean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@make clean -C $(LIB)
	@rm -rf obj

# fclean:	clean
# 	@make fclean -C $(LIB)
# 	@rm -rf $(NAME) test

# removed prerequisite of clean to fclean to eliminte repeated printf text
fclean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@printf "Deleting$(YELLOW)$(BOLD)   ./$(NAME)$(END) binaries$(END_TPUT)\n"
	@rm -rf obj
	@rm -rf $(NAME)
	@rm -rf $(wildcard *.dSYM)
	@make fclean -C $(LIB)
#	@printf "$(GREEN)$(BOLD)Complete!$(END)$(END_TPUT)\n"

test: test.c $(NAME)
	@$(CC) -o $@ -Wall -Wextra -g $(INC) $^

re:	fclean all
