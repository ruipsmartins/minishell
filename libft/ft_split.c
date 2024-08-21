/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:18:53 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/28 16:43:34 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer. */

static int	count_words(char const *str, char c)
{
	int		count;
	int		i;

	if (ft_strlen(str) == 0)
		return (0);
	count = 1;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*ft_words(char const *str, int inicio, int fim)
{
	char	*word;
	int		i;

	word = (char *)malloc((fim - inicio + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (inicio < fim)
	{
		word[i] = str[inicio];
		i++;
		inicio++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**box;
	int		inicio;
	size_t	fim;
	int		j;

	box = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!box)
		return (NULL);
	fim = 0;
	j = 0;
	inicio = -1;
	while (fim <= ft_strlen(s))
	{
		if (s[fim] != c && inicio == -1)
			inicio = fim;
		else if ((s[fim] == c || fim == ft_strlen(s)) && inicio >= 0)
		{
			box[j] = ft_words(s, inicio, fim);
			j++;
			inicio = -1;
		}
		fim++;
	}
	box[j] = NULL;
	return (box);
}
/* 
#include <stdio.h>

int	main(void)
{
	char	*str = "hello to this world!";
	char	c = ' ';
	int	i;
	char	**box;

	box = ft_split(str, c);
	i = 0;
	while (box[i])
	{
		printf("%d --> %s\n", i, box[i]);
		free(box[i]);
		i++;
	}
	free(box[i]);
	free(box); 
	return (0);
}
   */