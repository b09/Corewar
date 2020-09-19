/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprado <bprado@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 18:13:22 by bprado        #+#    #+#                 */
/*   Updated: 2020/09/18 13:31:22 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_cursor(t_cursor *cursor)
{
	// remove?
	ft_printf("id: %d ", cursor->id);
	// ft_printf("carry: %d ", cursor->carry);
	ft_printf("opcode: %d ", cursor->opcode);
	// ft_printf("last_live: %d ", cursor->last_live);
	// ft_printf("wait_cycle: %d ", cursor->wait_cycle);
	// ft_printf("positions: %d ", cursor->position);
	// ft_printf("jump %d ", cursor->jump);
	ft_printf("reg[0]: %d ", cursor->registry[0]);
	// ft_printf("reg[1]: %d ", cursor->registry[1]);
	// ft_printf("reg[2]: %d ", cursor->registry[2]);
	// ft_printf("reg[3]: %d ", cursor->registry[3]);
	// ft_printf("reg[4]: %d\n", cursor->registry[4]);
	ft_putchar('\n');
}

int				print_error(t_arena *arena, char *str)
{
	ft_printf("%s", str);
	free_everything(arena);
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
	free_everything(arena);
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
		free_everything(arena);
	}
	return (0);
}
