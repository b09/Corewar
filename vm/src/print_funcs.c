/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/16 15:25:52 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				print_error(char *str)
{
	ft_printf("%s", str);
	exit(1);
}

void			intro_champs(t_arena *arena)
{
	int			i;
	t_champ		*champ;

	i = 0;
	champ = NULL;
	ft_printf("\nLLLeetttttt'sss get reaaddyyyyyy to SEGFAUUULLLT!!!!!!\n");
	ft_printf("\tWOohoo!! Yeahhhhhh!! (crowd cheeers)\n\n");
	ft_printf("Introducing contestants...\n");
	while (i < arena->num_champs)
	{
		champ = arena->champs[i];
		ft_printf("Player %d, weighing in at %d bytes, \"%s\" (%s)\n", i + 1, \
		champ->real_exec_size, champ->name, champ->comment);
		++i;
	}
}

void			print_winner(t_arena *arena)
{
	ft_printf("\nContestant %d, \"%s\", has won !\n",
	arena->champs[arena->last_champ_alive - 1]->id,
	arena->champs[arena->last_champ_alive - 1]->name);
	exit(1); // free all malloced calls. 
}

int				print_hexdump(t_arena *arena, bool execute_anyway)
{
	int			i;

	i = 0;
	if ((arena->dump != -1 && arena->cycles == arena->dump) || execute_anyway)
	{
		while (i < MEM_SIZE)
		{
			if (i == 0)
				ft_printf("0x0000 : ");
			if (i && (i % HEXDUMP_WIDTH) == 0)
				ft_printf("\n%#06x : ", i);
			ft_printf("%02x ", arena->field[i]);
			++i;
		}
		ft_printf("\n");
		// exit(1);// uncomment line
	}
	return (0);
}

/*
**		DEBUG FUNCTIONS ARE BELOW **************************************
*/

void		print_champs(t_arena *arena)
{
	int			i;
	t_champ 	**champs;
	t_champ 	*champ;

	ft_printf("*** %s() ***\n", __func__);
	i = 0;
	while (i < arena->num_champs)
	{
		// champ = arena->champs;
		// // champ = champs[0];
		// ft_printf("addr:%p\n", champ[i]);
		// ft_printf("id:%d\n", champ[i].id);
		// ft_printf("name:%s\n", champ[i].name);
		// ft_printf("comment:%s\n", champ[i].comment);
		// ft_printf("exec_size:%d\n", champ[i].exec_size);
		// ft_printf("file_name:%s\n", champ[i].file_name);
		// ft_printf("file_size:%d\n\n", champ[i].file_size);
		// ++i;
		champ = arena->champs[i];
		// champ = champs[0];
		ft_printf("addr: %p\n", champ);
		ft_printf("id: %d\n", champ->id);
		ft_printf("name: %s\n", champ->name);
		ft_printf("comment: %s\n", champ->comment);
		ft_printf("real_exec_size: %d\n", champ->real_exec_size);
		ft_printf("file_name: %s\n", champ->file_name);
		ft_printf("file_size: %d\n\n", champ->file_size);
		++i;
	}
}

void			print_cursor(t_cursor *cursor)
{
	ft_printf("\nid: %d  ", cursor->id);
	ft_printf("carry: %d  ", cursor->carry);
	ft_printf("opcode: %d  ", cursor->opcode);
	ft_printf("last_live: %d  ", cursor->last_live);
	ft_printf("wait_cycle: %d  ", cursor->wait_cycle);
	ft_printf("positions: %d  ", cursor->position);
	ft_printf("jump %d\n\n", cursor->jump);
}

void			print_arena_and_cursors(t_arena *arena)
{
	int			reg_i;
	t_cursor	*cursor;

	cursor = arena->cursor_head;
	ft_printf("dump num: %d\n", arena->dump);
	ft_printf("num_champs: %d\n", arena->num_champs);
	ft_printf("num_cursors: %d\n", arena->num_cursors);
	ft_printf("cycles: %d\n", arena->cycles);
	ft_printf("cycles_to_die: %d\n", arena->cycles_to_die);
	while (cursor)
	{
		cursor = arena->cursor_head;
		reg_i = 0;
		while(reg_i < REG_NUMBER)
		{
			ft_printf("reg[%d]: %d\n", reg_i, cursor->registry[reg_i]);
			++reg_i;
		}
		cursor = cursor->next;
	}
	ft_printf("test arr[14]: %d\n", arena->wait_cycle_arr[14]);
}
