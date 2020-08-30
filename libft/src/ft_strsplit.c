/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fmiceli <fmiceli@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/25 14:41:45 by fmiceli       #+#    #+#                 */
/*   Updated: 2019/01/31 13:47:09 by fmiceli       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strsplit_count_words(char const *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			n++;
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
		}
		i++;
	}
	return (n);
}

static int	strsplit_next_word_start(char const *s, int start, char c)
{
	int i;

	i = start;
	while (s[i] == c)
		i++;
	return (i);
}

static int	strsplit_next_word_len(char const *s, int start, char c)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)&s[start];
	while (str[len] != c && str[len] != '\0')
		len++;
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		nwords;
	int		i;
	int		start;
	int		wordlen;

	nwords = strsplit_count_words(s, c);
	arr = (char **)malloc(sizeof(char **) * (nwords + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] == c)
		start++;
	while (i < nwords)
	{
		start = strsplit_next_word_start(s, start, c);
		wordlen = strsplit_next_word_len(s, start, c);
		arr[i] = ft_strsub(s, start, wordlen);
		start += wordlen;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
