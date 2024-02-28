#include "shell.h"

/**
 * ft_cwords - this function counts the words in a string
 * @s: the string
 * @c: the delimiter
 * Return: returns number of words found in a string
 */
static unsigned int	ft_cwords(const char *s, char c)
{
	unsigned int	count;
	int				n_word;

	n_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!n_word)
			{
				count++;
				n_word = 1;
			}
		}
		else
			n_word = 0;
		s++;
	}
	return (count);
}

/**
 * lwords - number of charcter in the string based on a delimiter
 * @str: the string to look into
 * @c: the delimiter
 * Return: returns the number of found charcter
 */
static unsigned int	lwords(char const *str, char c)
{
	unsigned int	l;

	l = 0;
	while (*str && *str != c)
	{
		l++;
		str++;
	}
	return (l);
}

/**
 * free_strings - this function for freeing the strings
 * @strings: the strings to be freed
 * @l: number of strings in strings
 */
static void	free_strings(char **strings, int l)
{
	int	i;

	i = -1;
	while (++i <= l)
		free(strings[i]);
	free(strings);
}

/**
 * ft_coping - this function copies the strings in the array of strings
 * @strings: the array of strings to be copied to
 * @s: the main string
 * @n_words: the number of words
 * @c: the dilimiter
 * Return: it returns the splited array
 */
char	**ft_coping(char **strings, char const *s, unsigned int n_words, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < n_words)
	{
		while (*s == c)
			s++;
		strings[i] = (char *)malloc(sizeof(char) * lwords(s, c) + 1);
		if (!strings[i])
		{
			free_strings(strings, i);
			return (NULL);
		}
		j = 0;
		while (*s && *s != c)
			strings[i][j++] = *s++;
		strings[i++][j] = '\0';
	}
	strings[i] = NULL;
	return (strings);
}
/**
 * _strtok - the function that splits the string
 * @s: the string to be splited
 * @c: the dilimiter
 * Return: an array of strings that have the splited strings
 */
char	**_strtok(char const *s, char c)
{
	char			**strings;
	unsigned int	n_words;

	if (!s)
		return (NULL);
	n_words = ft_cwords(s, c);
	strings = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!strings)
		return (NULL);
	return (ft_coping(strings, s, n_words, c));
}


