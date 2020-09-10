/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/10 16:02:30 by macbook       ########   odam.nl         */
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
*/

void		op_live(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->last_live = arena->cycles;
	cursor->jump = 5;
	arena->num_lives++;
	if (argument_valid() && arena->alive_champs_arr[(cursor->id * -1) - 1])
	{
		arena->last_champ_alive = cursor->registry[0] * -1;
	}
// FROM COREWAR PDF:
// For each valid execution of the live instruction, the machine must display:
// “A process shows that player X (champion_name) is alive”. 
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

void		op_ld(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (args[FIRST_ARG][SIZE] == SIZE_LDIR)
		cursor->registry[args[SECND_ARG][T_REG]] = args[FIRST_ARG][1];
	else
	{
		position = position + (ustr_to_int(args[FIRST_ARG][1]) % IDX_MOD);
		ft_memcpy(cursor->registry[args[SECND_ARG][1]], arena->field[position % MEM_SIZE], );
		
	}
		cursor->carry = args[FIRST_ARG][1] ? 0 : 1;
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
**			int position = position + (1)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(2)T_REG[i] = value
*/

void		op_st(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
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
**		(3)T_REG[i] = (2)T_DIR[i] + (1)T_DIR[i]
**
**		if (3)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_add(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	cursor->jump = 5;
	num = 0;
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (num == 0)
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
**		(3)T_REG[i] = (1)T_DIR[i] - (2)T_DIR[i]
**
**		if (3)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_sub(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	cursor->jump = 5;
	num = 0;
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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
**		if ARG1 or ARG2 == T_REG or T_DIR
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

void		op_and(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	cursor->jump += get_arg_size((position + 1) % MEM_SIZE, 1, 0);
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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
**		if ARG1 or ARG2 == T_REG or T_DIR
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

void		op_or(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	cursor->jump += get_arg_size((position + 1) % MEM_SIZE, 1, 0);
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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
**		if ARG1 or ARG2 == T_REG or T_DIR
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

void		op_xor(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	cursor->jump += get_arg_size((position + 1) % MEM_SIZE, 1, 0);
	populate_arguments(arena->field, cursor->position, args, 0);

	if (num == 0)
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
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			cursor->jump = value
**
**		if cursor->carr == 0
**			return ;
*/

void		op_zjmp(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3;
	if (cursor->carry)
		cursor->jump = FALSE; //FALSE is placeholder, finish statement
	else
		cursor->jump = 3;
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
**		if ARG1 or ARG2 == T_REG or T_DIR
**			(3)T_REG[i] = position + ((ARG1 + ARG2) % IDX_MOD)
**
**		if ARG1 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = position + ((ARG1 (or value) + ARG2) % IDX_MOD)
*/

void		op_ldi(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 1);
	cursor->jump += get_arg_size((position + 1) % MEM_SIZE, 1, 1);
	populate_arguments(arena->field, cursor->position, args, 1);

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
**			position = position + ((ARG2 + ARG3) % IDX_MOD)
**			field[position] = (1)T_REG[i];
**
**		if ARG2 == T_IND
**			int position = position + (2)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			field[position + ((ARG2 (or value) + ARG3) % IDX_MOD)] = (3)T_REG[i]
*/

void		op_sti(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 1, 1);
	cursor->jump += get_arg_size((position + 1) % MEM_SIZE, 2, 1);
	populate_arguments(arena->field, cursor->position, args, 1);

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

void		op_fork(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	cursor->jump = 3;
	create_cursor(arena, cursor->id);
	arena->cursor_head->position = (FALSE);// false is just placeholder, finish
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
**			(2)T_DIR[i] = (1)T_DIR[i]
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i]
**			int value = 4 bytes read at field[position]
**			(2)T_DIR[i] = value
**			
**		if (2)T_DIR[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_lld(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	populate_arguments(arena->field, cursor->position, args, 0);


	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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
**		if ARG1 or ARG2 == T_REG or T_DIR
**			(3)T_REG[i] = position + ARG1 + ARG2
**
**		if ARG1 == T_IND
**			int position = position + (1)T_IND[i] % IDX_MOD
**			int value = 4 bytes read at field[position]
**			(3)T_REG[i] = position + ARG1 (or value) + ARG2
**			
**		if (3)T_REG[i] == 0
**			carry = 1
**		else
**			carry = 0
*/

void		op_lldi(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	populate_arguments(arena->field, cursor->position, args, 1);


	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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

void		op_lfork(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	create_cursor(arena, cursor->id);
	arena->cursor_head->position = (FALSE);// false is just placeholder, finish
	cursor->jump = 3;
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

void		op_aff(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	populate_arguments(arena->field, cursor->position, args, 0);

}
