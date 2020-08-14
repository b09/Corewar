# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bprado <bprado@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/03 16:52:44 by bprado        #+#    #+#                  #
#    Updated: 2020/05/31 17:58:54 by macbook       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# https://stackoverflow.com/questions/14639794/getting-make-to-create-object-files-in-a-specific-directory
# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
# http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables


NAME 	= libftprintf.a

CFLAGS	= -Wall -Wextra -Werror -g

SRC 	= $(wildcard src/*.c)

LIB 	= ../libft

INC 	= -I inc -I ../libft/inc

OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))


all: $(NAME)

$(NAME): $(OBJ) ../libft/libft.a
	@echo "compiling ..."
	@cp ../libft/libft.a $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

obj/%.o: src/%.c inc/ft_printf.h
	@mkdir -p obj
	$(CC) -c $(CFLAGS) $(INC) -o $@ $<

../libft/libft.a: $(wildcard ../libft/*.c)
	@$(MAKE) -C $(LIB)

clean:
	@echo "cleaning ..."
	@make clean -C $(LIB)
	@rm -rf obj

fclean:	clean
	@make fclean -C $(LIB)
	@rm -rf $(NAME) test

test: test.c $(NAME)
	@$(CC) -o $@ -Wall -Wextra -g $(INC) $^

re:	fclean all
