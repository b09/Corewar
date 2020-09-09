/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/07 16:01:32 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// t_op				g_op_tab[17] =
// {
// 	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
// 	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
// 	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
// 	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
// 	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
// 	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
// 		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
// 	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
// 		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
// 	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
// 		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
// 	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
// 	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
// 		"load index", 1, 1},
// 	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
// 		"store index", 1, 1},
// 	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
// 	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
// 	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
// 		"long load index", 1, 1},
// 	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
// 	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
// 	{0, 0, {0}, 0, 0, 0, 0, 0}
// };

/*
**	all funcs() will have to adjust cursor->jump when getting arguments for
**	the required operation. the cursor position will be update in the game
**	loop by whatever it's current position is plus the cursor->jump value
*/

// arg sizes:
// reg == 1
// dir == 2 | 4
// ind == 2

/*
**	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}
*/

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
	cursor->jump = (arena->field[cursor->position][1] & 0x03 == IND_CODE) ? 5 : 7;
	return ;
}

/*
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0}
*/
void		op_st(t_cursor *cursor, t_arena *arena)
{
	// op_1 + enc_1 + reg_1 + (reg_1 | ind_2) == 4 | 5;
	cursor->jump = (arena->field[cursor->position][1] & 0x0C == (REG_CODE << 2)) ? 4 : 5;
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
	cursor->jump = 5;
	if ((arena->field[cursor->position][1] & 0x03 != REG_CODE))
		cursor->jump += ((arena->field[cursor->position][1] & 0x03 == IND_CODE) ? 1 : 3);
	if ((arena->field[cursor->position][1] & 0x0C != (REG_CODE << 2)))
		cursor->jump += ((arena->field[cursor->position][1] & 0x0C == (IND_CODE << 2)) ? 1 : 3);
	return ;
}

/*
**	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
**		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0}
*/
void		op_or(t_cursor *cursor, t_arena *arena)
{
	// cursor->jump same as op_and
	cursor->jump = 5;
	if ((arena->field[cursor->position][1] & 0x03 != REG_CODE))
		cursor->jump += ((arena->field[cursor->position][1] & 0x03 == IND_CODE) ? 1 : 3);
	if ((arena->field[cursor->position][1] & 0x0C != (REG_CODE << 2)))
		cursor->jump += ((arena->field[cursor->position][1] & 0x0C == (IND_CODE << 2)) ? 1 : 3);
	return ;
}

/*
**	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
**		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0}
*/
void		op_xor(t_cursor *cursor, t_arena *arena)
{
	// cursor->jump same as op_and
	cursor->jump = 5;
	if ((arena->field[cursor->position][1] & 0x03 != REG_CODE))
		cursor->jump += ((arena->field[cursor->position][1] & 0x03 == IND_CODE) ? 1 : 3);
	if ((arena->field[cursor->position][1] & 0x0C != (REG_CODE << 2)))
		cursor->jump += ((arena->field[cursor->position][1] & 0x0C == (IND_CODE << 2)) ? 1 : 3);
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
	cursor->jump = 3;
	cursor->jump += (arena->field[cursor->position][1] & 0x03 == REG_CODE) 1 ? : 2;
	cursor->jump += (arena->field[cursor->position][1] & 0x0C == (REG_CODE << 2)) 1 ? : 2;
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
	cursor->jump = 3;
	cursor->jump += (arena->field[cursor->position][1] & 0x0C == (REG_CODE << 2)) 1 ? : 2;
	cursor->jump += (arena->field[cursor->position][1] & 0x30 == (REG_CODE << 4)) 1 ? : 2;
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
	cursor->jump = (cursor->jump += (arena->field[cursor->position][1] & 0x0C == (DIR_CODE << 2)) ? 7 : 5;
	return ;
}

/*
**	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**		"long load index", 1, 1}
*/
void		op_lldi(t_cursor *cursor, t_arena *arena)
{
	// jump same as op_ldi
	cursor->jump = (cursor->jump += (arena->field[cursor->position][1] & 0x0C == (DIR_CODE << 2)) ? 7 : 5;
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
