/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:16:59 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/12 15:17:01 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static bool	ft_isop_split(const char *s, const char *op)
{
	if (!s || !op)
		return (false);
	else if (ft_strncmp(s, op, ft_strlen(op)) == 0)
		return (true);
	else
		return (false);
}

int	ft_get_op_len(const char *s)
{
	if (!s)
		return (0);
	else if (ft_isop_split(s, CMD_AND))
		return ((int)ft_strlen(CMD_AND));
	else if (ft_isop_split(s, CMD_OR))
		return ((int)ft_strlen(CMD_OR));
	else if (ft_isop_split(s, CMD_PIPE))
		return ((int)ft_strlen(CMD_PIPE));
	else if (ft_isop_split(s, CMD_HEREDOC))
		return ((int)ft_strlen(CMD_HEREDOC));
	else if (ft_isop_split(s, CMD_IN))
		return ((int)ft_strlen(CMD_IN));
	else if (ft_isop_split(s, CMD_OUT_APPEND))
		return ((int)ft_strlen(CMD_OUT_APPEND));
	else if (ft_isop_split(s, CMD_OUT))
		return ((int)ft_strlen(CMD_OUT));
	else
		return (0);
}

size_t	ft_quote_len(const char *s)
{
	size_t	len;
	char	quote;

	if (!ft_strchr("\'\"", s[0]))
		return (0);
	quote = s[0];
	len = 1;
	while (s[len] && quote != s[len])
		len++;
	return (len + 1);
}

size_t	ft_parenthesis_len(const char *s)
{
	size_t	len;
	size_t	counter;

	if (s[0] != '(')
		return (0);
	len = 1;
	counter = 1;
	while (s[len] && counter > 0)
	{
		if (s[len] == '(')
			counter++;
		else if (s[len] == ')')
			counter--;
		len++;
	}
	return (len);
}

char	**ft_free_strarr_until(char **arr, size_t position)
{
	size_t	i;

	i = 0;
	while (i < position)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
