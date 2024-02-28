#include "shell.h"

/**
 * _strlen - counts the length of a string
 * @s: the string
 * Return: returns the length of the string
 */
int _strlen(const char *s)
{
		int len = 0;

		if (!s)
			return (0);
		while (s[len])
			len++;
		return (len);
}

/**
 * _strncmp - comapire 2 strings returns 0 if they are equal
 * @s1: the first string
 * @s2: the second string
 * @n: the size of bytes to compaire
 * n@: number of bytes to compaire
 * Return: 0 they are equal, the diffrence otherwise
*/
int     _strncmp(const char *s1, const char *s2, size_t n)
{
		size_t  len;

		len = 0;
		while (len < n)
		{
			if ((unsigned char)s1[len] > (unsigned char)s2[len])
				return (1);
			else if ((unsigned char)s1[len] < (unsigned char)s2[len])
				return (-1);
			else if ((unsigned char)s1[len] == 0 || (unsigned char)s2[len] == 0)
				return ((unsigned char)s1[len] - (unsigned char)s2[len]);
			len++;
		}
		return (0);
}

/**
 * _strlcat - concatenaite dest and src into the dest
 * @dst: the distination
 * @src: the source to concatenate from
 * @size: size of bytes to concate
 * Return: the lenght of the source
 */
size_t  _strlcat(char *dst, const char *src, size_t size)
{
	size_t  l_dst;
	size_t  l_src;
	size_t  len;

	len = 0;
	if (dst == NULL && size == 0)
		return (_strlen(src));
	l_dst = _strlen(dst);
	l_src = _strlen(src);
	if (l_dst >= size || size == 0)
		return (l_src + size);
	while (src[len] && len < size - l_dst - 1)
	{
		dst[len + l_dst] = src[len];
		len++;
	}
	dst[len + l_dst] = '\0';
	return (l_dst + l_src);
}
/**
 * _strlcpy - copies from src to dest
 * @dst: the distination
 * @src: the source to copy from
 * @size: size of the buffer
 * Return: the size of buffer
 */
size_t  _strlcpy(char *dst, const char *src, size_t size)
{
	size_t  lsrc;
	size_t  len;

	lsrc = _strlen(src);
	len = 0;
	if (size > 0)
	{
		while (len < size - 1 && src[len] != '\0')
		{
			dst[len] = src[len];
			len++;
		}
		dst[len] = '\0';
	}
	return (lsrc);
}

