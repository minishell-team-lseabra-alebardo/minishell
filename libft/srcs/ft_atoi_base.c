/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:17:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/09/30 15:44:21 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * validate_base - Checks if the provided base string is valid for conversion.
 *
 * @param base: The string representing the base characters.
 *
 * Return: 1 if the base is valid (at least two unique characters, no
 * duplicates, and no '+', '-', or space), otherwise returns 0.
 */
static int	validate_base(char *base)
{
	int	i;
	int	j;
	int	size;

	size = ft_strlen(base);
	if (size <= 1)
		return (0);
	i = 0;
	while (base[i] != 0)
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		j = i + 1;
		while (base[j] != 0)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * validate_char - Checks if a character exists in the base string.
 *
 * @param c: The character to check.
 * @param base: The string representing the base characters.
 *
 * Return: 1 if the character is found in the base, otherwise returns 0.
 */
static int	validate_char(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (base[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * find_position - Finds the index of a character in the base string.
 *
 * @param c: The character to find.
 * @param base: The string representing the base characters.
 *
 * Return: the index of the character in the base string, or the length of the 
 * base if not found.
 */
static int	find_position(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] != 0)
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/**
 * ft_atoi_base - Converts a string representing a number in a given base to an 
 * integer.
 *
 * @param str: The string containing the number to convert.
 * @param base: The string representing the valid characters of the base 
 * (e.g., "0123456789ABCDEF").
 *
 * Parses the input string `str`, interprets it as a number in the base 
 * specified by `base`, and returns its integer value. Handles optional leading 
 * whitespace and sign characters.
 * Return: 0 if the base is invalid or the string contains invalid characters.
 */
int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	if (!validate_base(base))
		return (result);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (validate_char(str[i], base))
	{
		if (find_position(str[i], base) >= (int)ft_strlen(base))
			return (result * sign);
		result = result * ft_strlen(base) + find_position(str[i], base);
		i++;
	}
	return (result * sign);
}
