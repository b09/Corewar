PRINTF			= ft_printf/
LIBFT			= libft/
ASSEMBLER		= assembler/
VIRTUAL_MACHINE	= vm/

all: make

make:
	@make -C $(LIBFT)
	@make -C $(PRINTF)
	@make -C $(ASSEMBLER)
	@make -C $(VIRTUAL_MACHINE)

clean:
	@make -C $(LIBFT) clean
	@make -C $(PRINTF) clean
	@make -C $(ASSEMBLER) clean
	@make -C $(VIRTUAL_MACHINE) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean
	@make -C $(ASSEMBLER) fclean
	@make -C $(VIRTUAL_MACHINE) fclean

re: fclean all

