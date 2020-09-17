/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/17 11:22:07 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**	all funcs() will have to adjust cursor->jump when getting arguments for
**	the required operation. the cursor position will be update in the game
**	loop by whatever it's current position is plus the cursor->jump value
*/

/*
**		opcode;			= 1
**		*op_str;		= live
**		cycles;			= 10
**		*description;	= "alive"
**		changes carry;	= FALSE
**		args;			= (T_DIR)
**		encoding;		= 0
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 1
**	SIZE:	[1]	[4]
**			OP	ARGS
**	TOTAL SIZE:		5
**
**	FROM COREWAR PDF:
**	For each valid execution of the live instruction, the machine must display:
**	“A process shows that player X (champion_name) is alive”.
*/

void		op_live(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int		value;

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete

	(void)args;
	value = ustr_to_int(arena->field, position + 1, 4);
	cursor->last_live = arena->cycles;
	cursor->jump = 5;
	arena->num_lives++;
	// if (value > 0 && value <= arena->num_champs &&
	// 	value + cursor->registry[0] == 0 && arena->champs[value]->alive == TRUE)
	if (value > 0 && value <= arena->num_champs &&
		value + cursor->registry[0] == 0)
	{
		ft_printf("A process shows that player %d (%s) is alive.\n",
		value, arena->champs[value - 1]->name);
		arena->last_champ_alive = cursor->registry[0] * -1;
	}
}

/*
**		opcode;			= 2
**		*op_str;		= ld
**		cycles;			= 5
**		*description;	= "load"
**		changes carry;	= TRUE
**		args;			= (T_DIR | T_IND), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 2
**
**	SIZE:	[1]	[1]	[2-4][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 7
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 == T_DIR
**			(2)T_REG[i] = (1)T_DIR[i]
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(2)T_REG[i] = value
**
**		if (2)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_ld(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete

	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 2, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	// ft_printf("func:%s line %d, args content: %d %d\n", __func__, __LINE__, args->value_1, args->value_2);
	if (args->size_1 == SIZE_LDIR)
		cursor->registry[args->value_2 - 1] = args->value_1;
	else if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1 % IDX_MOD;
		position = ustr_to_int(arena->field, position, 4);
		cursor->registry[args->value_2 - 1] = position;
	}
	cursor->carry = cursor->registry[args->value_2 - 1] ? 0 : 1;
	// print_cursor(cursor);// delete

}

/*
**		opcode;			= 3
**		*op_str;		= st
**		cycles;			= 5
**		*description;	= "store"
**		changes carry;	= FALSE
**		args;			= (T_REG), (T_IND | T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (N/A)
**		number_of_args;	= 2
**
**	SIZE:	[1]	[1]	[1][1-2]
**			OP	EN	ARGS
**	TOTAL SIZE:		4 - 5
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG2 == T_REG
**			(2)T_REG[i] = (1)T_REG[i]
**
**		if ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			field[position] = (1)T_REG[i]


Type T_IND is related to the memory addresses, so st workflow is:

    Truncate indirect value by modulo: % IDX_MOD.

    Calculate the address: current address of the cursor + <SECOND_ARGUMENT> % IDX_MOD.

    Write the value from the registry passed as first argument into the memory address calculated in the previous step.

*/

void		op_st(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	// ft_printf("func:%s line %d, args content: %d %d\n", __func__, __LINE__, args->value_1, args->value_2);
	if (args->size_2 == SIZE_REG)
		cursor->registry[args->value_2 - 1] =
		cursor->registry[args->value_1 - 1];
	else if (args->size_2 == SIZE_IND)
	{
		position = (position + args->value_2) % IDX_MOD;
		int_to_ustr(cursor->registry[args->value_1 - 1],
										arena->field, position, 4);
	}
}

/*
**		opcode;			= 4
**		*op_str;		= add
**		cycles;			= 10
**		*description;	= "addition"
**		changes carry;	= TRUE
**		args;			= (T_REG), (T_REG), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (N/A)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1][1][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		(3)T_REG[i] = (2)T_REG[i] + (1)T_REG[i]
**
**		if (3)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_add(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	print_hexdump(arena, TRUE);
	populate_arguments(arena->field, position, args, 0);
	if (arena->field[position + 1] != 0x1008)
		return ;
	cursor->jump = 5;
	if (check_register_values(args, 1, 2, 3) == FALSE)
	{
		ft_printf("printd\n");
		return ;
	}
	cursor->registry[args->value_3 - 1] =
	cursor->registry[args->value_2 - 1] +
	cursor->registry[args->value_1 - 1];
	if (cursor->registry[args->value_3 - 1] == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
}

/*
**		opcode;			= 5
**		*op_str;		= sub
**		cycles;			= 10
**		*description;	= "subtract"
**		changes carry;	= TRUE
**		args;			= (T_REG), (T_REG), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (N/A)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1][1][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		(3)T_REG[i] = (1)T_REG[i] - (2)T_REG[i]
**
**		if (3)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_sub(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete

	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 1, 2, 3) == FALSE)
		return ;
	cursor->jump = 5;
	cursor->registry[args->value_3 - 1] =
	cursor->registry[args->value_1 - 1] -
	cursor->registry[args->value_2 - 1];
	if (cursor->registry[args->value_3 - 1] == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
	print_hexdump(arena, TRUE);
}

static int	op_and_helper(t_args *args, int position, t_arena *arena)
{
	int		value1;
	int		value2;

	value1 = 0;
	value2 = 0;
	if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1 % IDX_MOD;
		value1 = ustr_to_int(arena->field, position, 4);
	}
	else
		value1 = args->value_1;
	if (args->size_2 == SIZE_IND)
	{
		position = position + args->value_2 % IDX_MOD;
		value2 = ustr_to_int(arena->field, position, 4);
	}
	else
		value2 = args->value_2;
	return (value1 & value2);
}

/*
**		opcode;			= 6
**		*op_str;		= and
**		cycles;			= 6
**		*description;	= "and"
**		changes carry;	= TRUE
**		args;			=(T_REG | T_DIR | T_IND),(T_REG | T_IND | T_DIR),(T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1-4][1-4][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 11
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 and ARG2 != T_IND
**			(3)T_REG[i] = ARG1 & ARG2 (bitwise &)
**
**		if ARG1 or ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = ARG1 & value (bitwise &)
**
**		if (3)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_and(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 0, 3) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 != SIZE_IND && args->size_2 != SIZE_IND)
		cursor->registry[args->value_3 - 1] =
		cursor->registry[args->value_1 - 1] &
		cursor->registry[args->value_2 - 1]; // this doesn't look like the pseudocode
	else
		cursor->registry[args->value_3 - 1] =
										op_and_helper(args, position, arena);
	if (cursor->registry[args->value_3 - 1] == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
}

static int	op_or_helper(t_args *args, int position, t_arena *arena)
{
	int		value1;
	int		value2;

	value1 = 0;
	value2 = 0;
	if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1 % IDX_MOD;
		value1 = ustr_to_int(arena->field, position, 4);
	}
	else
		value1 = args->value_1;
	if (args->size_2 == SIZE_IND)
	{
		position = position + args->value_2 % IDX_MOD;
		value2 = ustr_to_int(arena->field, position, 4);
	}
	else
		value2 = args->value_2;
	return (value1 | value2);
}

/*
**		opcode;			= 7
**		*op_str;		= or
**		cycles;			= 6
**		*description;	= "or"
**		changes carry;	= TRUE
**		args;			=(T_REG | T_IND | T_DIR),(T_REG | T_IND | T_DIR),(T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1-4][1-4][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 11
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 and ARG2 != T_IND
**			(3)T_REG[i] = ARG1 | ARG2 (bitwise |)
**
**		if ARG1 or ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = ARG1 | value (bitwise |)
**
**		if (3)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_or(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 0, 3) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 != SIZE_IND && args->size_2 != SIZE_IND)
		cursor->registry[args->value_3 - 1] =
		cursor->registry[args->value_1 - 1] |
		cursor->registry[args->value_2 - 1];
	else
		cursor->registry[args->value_3 - 1] =
											op_or_helper(args, position, arena);
	if (cursor->registry[args->value_3 - 1] == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
}

static int	op_xor_helper(t_args *args, int position, t_arena *arena)
{
	int		value1;
	int		value2;

	value1 = 0;
	value2 = 0;
	if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1 % IDX_MOD;
		value1 = ustr_to_int(arena->field, position, 4);
	}
	else
		value1 = args->value_1;
	if (args->size_2 == SIZE_IND)
	{
		position = position + args->value_2 % IDX_MOD;
		value2 = ustr_to_int(arena->field, position, 4);
	}
	else
		value2 = args->value_2;
	return (value1 ^ value2);
}

/*
**		opcode;			= 8
**		*op_str;		= xor
**		cycles;			= 6
**		*description;	= "xor"
**		changes carry;	= TRUE
**		args;			=(T_REG | T_IND | T_DIR),(T_REG | T_IND | T_DIR),(T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1-4][1-4][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 11
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 and ARG2 != T_IND
**			(3)T_REG[i] = ARG1 ^ ARG2 (bitwise ^)
**
**		if ARG1 or ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = ARG1 ^ value (bitwise ^)
**
**		if (3)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_xor(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete

	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 0, 3) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 != SIZE_IND && args->size_2 != SIZE_IND)
		cursor->registry[args->value_3 - 1] =
		cursor->registry[args->value_1 - 1] ^
		cursor->registry[args->value_2 - 1];
	else
		cursor->registry[args->value_3 - 1] =
										op_xor_helper(args, position, arena);
	if (cursor->registry[args->value_3 - 1] == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
}

/*
**		opcode;			= 9
**		*op_str;		= zjmp
**		cycles;			= 20
**		*description;	= "jump if zero"
**		changes carry;	= FALSE
**		args;			= (T_DIR)
**		encoding;		= 0
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 1
**
**	SIZE:	[1]	[2]
**			OP	ARGS
**	TOTAL SIZE:		3
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if cursor->carry == 1
**			int position = position + (1)T_DIR[i] % IDX_MOD
**			int value = 2 bytes read at field[position]
**			cursor->jump = value
**
**		if cursor->carry == 0
**			cursor->jump = 3 (size of op with args)
*/

void		op_zjmp(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__);

	int		value;

	(void)args;
	value = 3;
	if (cursor->carry)
		value = ustr_to_int(arena->field, (position + 1) % MEM_SIZE, 2);
	ft_printf("value: %d\n", value); //delete
	cursor->jump = value % IDX_MOD;
	// print_cursor(cursor);// delete
}

/*
**		opcode;			= 10
**		*op_str;		= ldi
**		cycles;			= 25
**		*description;	= "load index"
**		changes carry;	= FALSE
**		args;			= (T_REG | T_DIR | T_IND), (T_DIR | T_REG), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1-2][1-2][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 7
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 != T_IND
**			(3)T_REG[i] = field[position + ((ARG1 + ARG2) % IDX_MOD)] 4 bytes
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[new position]
**			(3)T_REG[i] = field[old position + ((ARG1 (or value) + ARG2)\
**						% IDX_MOD)] 4 bytes
*/

void		op_ldi(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int		value;

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, cursor->position, args, 1);
	if (check_register_values(args, 0, 0, 3) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;

	if (args->size_1 != SIZE_IND)
		cursor->registry[args->value_3 - 1] =
		ustr_to_int(arena->field, position + ((args->value_1
		+ args->value_2) % IDX_MOD), 4);
	else
	{
		value = ustr_to_int(arena->field, position +
								(args->value_1 % IDX_MOD), 4);
		cursor->registry[args->value_3 - 1] =
		ustr_to_int(arena->field, position + (value +
								args->value_2) % IDX_MOD, 4);
	}
}

/*
**		opcode;			= 11
**		*op_str;		= sti
**		cycles;			= 25
**		*description;	= "store index"
**		changes carry;	= FALSE
**		args;			= (T_REG), (T_REG | T_DIR | T_IND), (T_DIR | T_REG)
**		encoding;		= 1
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1][1-2][1-2]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 7
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG2 == T_REG or T_DIR
**			new position = position + ((ARG2 + ARG3) % IDX_MOD)
**			field[new position] = (1)T_REG[i];
**
**		if ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			field[position + ((ARG2 (or value) + ARG3) % IDX_MOD)] = (1)T_REG[i]
*/

void		op_sti(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, cursor->position, args, 1);
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	// print_hexdump(arena, TRUE);
	ft_putchar('\n');
	if (args->size_2 != SIZE_IND)
	{
		position = position + args->value_2 +
									args->value_3 % IDX_MOD;
		int_to_ustr(cursor->registry[args->value_1 - 1],
							arena->field, position, 4);
	}
	else
	{
		int_to_ustr(cursor->registry[args->value_1 - 1],
						arena->field, position +
						(args->value_2 + args->value_3 % IDX_MOD), 4);
	}
	// print_hexdump(arena, TRUE);
}

/*
**		opcode;			= 12
**		*op_str;		= fork
**		cycles;			= 800
**		*description;	= "fork"
**		changes carry;	= FALSE
**		args;			= (T_DIR)
**		encoding;		= 0
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 1
**
**	SIZE:	[1]	[2]
**			OP	ARGS
**	TOTAL SIZE:		3
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		new cursor = current cursor
**		new cursor->position = old_position + T_DIR[i] % IDX_MOD
*/

void		op_fork(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int val;

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	(void)args;
	cursor->jump = 3;
	create_cursor(arena, cursor->id);
	val = ustr_to_int(arena->field, position + 1, 2);
	arena->cursor_head->position = (position +
						(val % IDX_MOD) % MEM_SIZE);
	arena->num_cursors++;
}

/*
**		opcode;			= 13
**		*op_str;		= lld
**		cycles;			= 10
**		*description;	= "long load"
**		changes carry;	= TRUE
**		args;			= (T_DIR | T_IND), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (4 byte T_DIR)
**		number_of_args;	= 2
**
**	SIZE:	[1]	[1]	[2-4][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 7
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 == T_DIR
**			(2)T_REG[i] = (1)T_DIR[i]
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i]
**			int value = 4 bytes read at field[position]
**			(2)T_REG[i] = value
**
**		if (2)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_lld(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 1, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 == SIZE_LDIR)
		cursor->registry[args->value_2 - 1] = args->value_1;
	else if (args->size_1 == SIZE_IND)
	{
		position = position + args->value_1;
		position = ustr_to_int(arena->field, position, 4);
		cursor->registry[args->value_2 - 1] = position;
	}
	cursor->carry = cursor->registry[args->value_2 - 1] ? 0 : 1;
}

/*
**		opcode;			= 14
**		*op_str;		= lldi
**		cycles;			= 50
**		*description;	= "long load index"
**		changes carry;	= TRUE
**		args;			= (T_REG | T_DIR | T_IND), (T_DIR | T_REG), (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 3
**
**	SIZE:	[1]	[1]	[1-2][1-2][1]
**			OP	EN	ARGS
**	TOTAL SIZE:		5 - 7
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		if ARG1 != T_IND
**			(3)T_REG[i] = field[position + ARG1 + ARG2] 4 bytes
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = field[position + ARG1 (or value) + ARG2] 4 bytes
**
**		if (3)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_lldi(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int		value;

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete

	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 0, 0, 1) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	if (args->size_1 != SIZE_IND)
		cursor->registry[args->value_3 - 1] =
		ustr_to_int(arena->field, position + args->value_1
		+ args->value_2, 4);
	else
	{
		value = ustr_to_int(arena->field, position +
								(args->value_1 % IDX_MOD), 4);
		cursor->registry[args->value_3 - 1] =
		ustr_to_int(arena->field, position + value +
								args->value_2, 4);
	}
}

/*
**		opcode;			= 15
**		*op_str;		= lfork
**		cycles;			= 1000
**		*description;	= "long fork"
**		changes carry;	= FALSE
**		args;			= (T_DIR)
**		encoding;		= 0
**		label_twobytes;	= 1 (2 byte T_DIR)
**		number_of_args;	= 1
**
**	SIZE:	[1]	[2]
**			OP	ARGS
**	TOTAL SIZE:		3
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		new cursor = current cursor
**		new cursor->position = old_position + T_DIR[i]
*/

void		op_lfork(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	int val;

	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	(void)args;
	cursor->jump = 3;
	create_cursor(arena, cursor->id);
	val = ustr_to_int(arena->field, position + 1, 2);
	arena->cursor_head->position = (position + val % MEM_SIZE);
	arena->num_cursors++;
}

/*
**		opcode;			= 16
**		*op_str;		= aff
**		cycles;			= 2
**		*description;	= "aff"
**		changes carry;	= FALSE
**		args;			= (T_REG)
**		encoding;		= 1
**		label_twobytes;	= 0 (N/A)
**		number_of_args;	= 1
**
**	SIZE:	[1]	[1]	[1]
**			OP	EN	ARGS
**	TOTAL SIZE:		3
**
**	PSEUDOCODE:		T_DIR refers to type, T_DIR[i] is value, (2)T_DIR is 2nd arg
**
**		putchar(T_REG[i]);
*/

void		op_aff(t_cursor *cursor, t_arena *arena, t_args *args,
			int position)
{
	ft_printf("func:%s line %d\n", __func__, __LINE__); //delete
	populate_arguments(arena->field, position, args, 0);
	if (check_register_values(args, 1, 0, 0) == FALSE)
		return ;
	cursor->jump = 2 + args->size_1 + args->size_2 + args->size_3;
	ft_printf("%c", cursor->registry[args->value_1 - 1]);
}
