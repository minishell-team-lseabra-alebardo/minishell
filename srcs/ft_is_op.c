/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:06:58 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/10 18:18:09 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

bool	ft_is_op(const char *s, const char *op)
{
	size_t	len;

	if (!s || !*s || !op)
		return (false);
	if (ft_strlen(s) > ft_strlen(op))
		len = ft_strlen(s);
	else
		len = ft_strlen(op);
	if (ft_strncmp(s, op, len) == 0)
		return (true);
	else
		return (false);
}

bool	ft_is_logic_or_pipe_op(char *str)
{
	bool	res;

	res = false;
	if (ft_is_op(str, CMD_AND))
		res = true;
	else if (ft_is_op(str, CMD_OR))
		res = true;
	else if (ft_is_op(str, CMD_PIPE))
		res = true;
	return (res);
}

bool	ft_is_redir_op(char *str)
{
	bool	res;

	while (ft_isdigit(*str))
		str++;
	res = false;
	if (ft_is_op(str, CMD_HEREDOC))
		res = true;
	else if (ft_is_op(str, CMD_IN))
		res = true;
	else if (ft_is_op(str, CMD_OUT_APPEND))
		res = true;
	else if (ft_is_op(str, CMD_OUT))
		res = true;
	return (res);
}
