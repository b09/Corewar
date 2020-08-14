PRINTF_PATH		= ft_printf/
LIBFT_PATH		= libft/
ASM_PATH		= assembler/
VM_PATH			= vm/

all: make

make:
	@make -C $(LIBFT_PATH)
	@make -C $(PRINTF_PATH)
	@make -C $(ASM_PATH)
	@make -C $(VM_PATH)

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(PRINTF_PATH) clean
	@make -C $(ASM_PATH) clean
	@make -C $(VM_PATH) clean

fclean:
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@make -C $(ASM_PATH) fclean
	@make -C $(VM_PATH) fclean

re: fclean all

