/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operations.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/06 19:25:12 by macbook       ########   odam.nl         */
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
**	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}
*/

void		op_live(t_cursor *cursor, t_arena *arena)
{
	return ;
}
/*
**	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0}
*/

void		op_ld(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0}
*/
void		op_st(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0}
*/
void		op_add(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0}
*/
void		op_sub(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0}
*/
void		op_and(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
**		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0}
*/
void		op_or(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
**		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0}
*/
void		op_xor(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1}
*/
void		op_zjmp(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**		"load index", 1, 1}
*/
void		op_ldi(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
**		"store index", 1, 1}
*/
void		op_sti(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1}
*/
void		op_fork(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0}
*/
void		op_lld(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**		"long load index", 1, 1}
*/
void		op_lldi(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1}
*/
void		op_lfork(t_cursor *cursor, t_arena *arena)
{
	return ;
}

/*
**	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
*/
void		op_aff(t_cursor *cursor, t_arena *arena)
{
	return ;
}
