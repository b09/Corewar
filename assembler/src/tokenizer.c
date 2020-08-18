/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>             +#+                   */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:31:22 by fmiceli       #+#    #+#                 */
/*   Updated: 2020/08/18 15:31:22 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**  Duplicates substring from start of str to next whitespace.
**  Updates *str, starting position of string after extracting current substring.
**  Also updates start, the index for starting position.
**
**  Params: str, a string starting at the first char of a token.
            start, the index of the starting character for next token.
**  Return: Literal string of a single token.
*/

static char *get_token_string(char **str, int *start)
{
    char    *end;

    end = *str;
    while (!ft_isspace(end))
        end++;
    (*start) = (*start) + (end - *str);
    token_string = ft_strndup(*str, end - *str);
    return (token_string);
}

/*
**  Tokenizes one line of asm.
**
**  Params: str, a single line from the source retrieved using gnl.
**                  expected to be sequential.
**  Return: head of list of new tokens, to be appended to the end of
**                  the complete list.
*/

t_list *tokenize(char *str)
{
    static int  line;
    int         start;
    t_list      *head;
    t_token     *token;

    line = 1;
    start = 1;
    while (str)
    {
        while (*str != '\n' && ft_isspace(*str))
        {
            start++;
            str++;
        }
        token = (t_token *)ft_memalloc(sizeof(t_token));
        token->line = line;
        token->start = start;
        token->token_string = get_token_string(&str, &start);
        token->type = get_token_type(token->token_string, token_hmap);
        ft_lstappend(head, ft_lstnew(token));
    }
    line++;
    return (head);
}
