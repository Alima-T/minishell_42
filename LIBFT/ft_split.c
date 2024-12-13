/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:14:06 by aokhapki          #+#    #+#             */
/*   Updated: 2024/03/26 16:46:11 by aokhapki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	h_word_count(char const *s, char c)
{
	int	word_nb;
	int	is_word;

	word_nb = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else
		{
			if (is_word == 0)
			{
				word_nb++;
				is_word = 1;
			}
		}
		s++;
	}
	return (word_nb);
}

char	**h_free_arrays(char **arrays)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = arrays;
	if (arrays)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
	}
	return (NULL);
}

char	*h_copy_word(const char *word_start, size_t word_len)
{
	char	*word;

	word = malloc(word_len + 1);
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, word_start, word_len);
	word[word_len] = '\0';
	return (word);
}

char	**h_helper(char const *s, const char *word_start, int *word_index,
		char **words)
{
	words[(*word_index)++] = h_copy_word(word_start, s - word_start);
	if (!words[(*word_index) - 1])
		return (h_free_arrays(words));
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char		**words;
	int			word_index;
	const char	*word_start;

	word_start = s;
	words = malloc((h_word_count(s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	word_index = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (s != word_start)
				if (!h_helper(s, word_start, &word_index, words))
					return (NULL);
			word_start = s + 1;
		}
		else if (*(s + 1) == '\0')
			if (!h_helper(s + 1, word_start, &word_index, words))
				return (NULL);
		s++;
	}
	words[word_index] = NULL;
	return (words);
}
