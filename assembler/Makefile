NAME		= ../asm
CFLAGS		= -Wall -Wextra -Werror -g
SRC			= $(wildcard src/*.c)
OBJ			= $(patsubst src/%.c,obj/%.o,$(SRC))
CC			= gcc
INC			= -I inc -I ../libft/inc -I ../ft_printf/inc
LIB			= ../libft
LIB_A		= ../libft/libft.a
PFLIB		= ../ft_printf
PFLIB_A		= ../ft_printf/libftprintf.a


all: $(NAME)

$(NAME): $(OBJ) ft_printf/libftprintf.a
	@$(CC) -o $@ $(CFLAGS) $(INC) $(OBJ) $(PFLIB_A)
	@printf " $(CYAN)$(BOLD)$(UNDERLINE)./$(NAME)$(END)$(END_TPUT) created\n"

obj/%.o: src/%.c inc/asm.h
	@mkdir -p obj
	@printf " $(GREEN)$(BOLD)✔$(END)$(END_TPUT) Object file for \
	$(PURPLE)$(current_dir)/$<$(END)\n"
	@$(CC) -c $(CFLAGS) $(INC) -o $@ $<

ft_printf/libftprintf.a: $(wildcard ../ft_printf/*.c)
	@$(MAKE) -C $(PFLIB)

clean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@make clean -C $(LIB)
	@rm -rf obj

# removed prerequisite of clean to fclean to eliminte repeated printf text
fclean:
	@printf "Cleaning$(BOLD)   $(NAME) object files$(END_TPUT)\n"
	@printf "Deleting$(YELLOW)$(BOLD)   ./$(NAME)$(END) binaries$(END_TPUT)\n"
	@rm -rf obj
	@rm -rf $(wildcard *.dSYM)
	@rm -rf $(NAME)
	@make fclean -C $(PFLIB)
	@printf "$(GREEN)$(BOLD)Complete!$(END)$(END_TPUT)\n"

re: fclean all

all: $(NAME)
