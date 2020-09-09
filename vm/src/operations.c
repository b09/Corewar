/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/09 20:24:55 by macbook       ########   odam.nl         */
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
*/

void		op_ld(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	int		num;

	num = 0;
	cursor->jump = 3 + get_arg_size((position + 1) % MEM_SIZE, 0, 0);
	if (populate_arguments(arena->field, position, args, 0) == 0)
		return ;
	if (args[0][0] == SIZE_LDIR)
	{
		
	}
	if (num == 0)
		cursor->carry = TRUE;
	else
		cursor->carry = FALSE;
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
			OP	EN	ARGS
**	TOTAL SIZE:		5
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
*/

void		op_aff(t_cursor *cursor, t_arena *arena, unsigned char **args,
			int position)
{
	populate_arguments(arena->field, cursor->position, args, 0);

}





************************************



void		op_live(t_cursor *cursor, t_arena *arena)
{
	// FROM COREWAR PDF:
	// For each valid execution of the live instruction, the machine must display:
	// “A process shows that player X (champion_name) is alive”.

 	// op_1 + dir_4 == 5
	cursor->jump = 5;
	return ;
}
/*
**	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0}
*/

void		op_ld(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + (dir_4 | ind_2) + reg_1 == 5 | 7;
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 0);
	return ;
}

/*
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0}
*/
void		op_st(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 + (reg_1 | ind_2) == 4 | 5;
	cursor->jump = 3 + get_arg_size(cursor, arena, 1, 0);
	return ;
}

/*
**	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0}
*/
void		op_add(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 + reg_1, + reg_1 == 5;
	cursor->jump = 5;
	return ;
}

/*
**	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0}
*/
void		op_sub(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 + reg_1, + reg_1 == 5;
	cursor->jump = 5;
	return ;
}

/*
**	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0}
*/
void		op_and(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 == 2;
	// += reg_1 | ind_2 | dir_4
	// += reg_1 | ind_2 | dir_4
	// += reg_1
	// == 5 | 6 | 7 | 8 | 9 | 10 | 11
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 0) +
		get_arg_size(cursor, arena, 1, 0);
	return ;
}

/*
**	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
**		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0}
*/
void		op_or(t_cursor *cursor, t_arena *arena)
{
	// cursor->jump same as op_and
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 0) +
		get_arg_size(cursor, arena, 1, 0);
	return ;
}

/*
**	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
**		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0}
*/
void		op_xor(t_cursor *cursor, t_arena *arena)
{
	// cursor->jump same as op_and
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 0) +
		get_arg_size(cursor, arena, 1, 0);
	return ;
}

/*
**	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1}
*/
void		op_zjmp(t_cursor *cursor, t_arena *arena)
{
	// op_1 + dir_2 == 3;
	// I could define structs/unions to retrieve values from specific fields,
	// but I'm hoping you already have some solution.
	cursor->jump = cursor->carry ? (VALUE AT ARG_1 % IDX_MOD) : 3;
	return ;
}

/*
**	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**		"load index", 1, 1}
*/

void		op_ldi(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 == 2;
	// += reg_1 | dir_2, ind_2
	// += reg_1 | dir_2
	// += reg_1
	// == 5, 6, 7
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 1) +
		get_arg_size(cursor, arena, 1, 1);
	return ;
}

/*
**	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
**		"store index", 1, 1}
*/
void		op_sti(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 == 3;
	// += reg_1 | dir_2, ind_2
	// += reg_1 | dir_2
	// == 5, 6, 7
	cursor->jump = 3 + get_arg_size(cursor, arena, 1, 1) +
		get_arg_size(cursor, arena, 2, 1);;
	return ;
}

/*
**	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1}
*/
void		op_fork(t_cursor *cursor, t_arena *arena)
{
	// op_1 + dir_2 == 3;
	cursor->jump = 3;
	return ;
}

/*
**	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0}
*/
void		op_lld(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 == 2;
	// += dir_4, ind_2
	// += reg_1
	// == 5, 7
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 0);
	return ;
}

/*
**	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**		"long load index", 1, 1}
*/
void		op_lldi(t_cursor *cursor, t_arena *arena)
{
	// jump same as op_ldi
	cursor->jump = 3 + get_arg_size(cursor, arena, 0, 1) +
		get_arg_size(cursor, arena, 1, 1);
	return ;
}

/*
**	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1}
*/
void		op_lfork(t_cursor *cursor, t_arena *arena)
{
	// op_1 + dir_2 == 3;
	cursor->jump = 3;
	return ;
}

/*
**	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
*/
void		op_aff(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 == 3;
	cursor->jump = 3;
	return ;
}