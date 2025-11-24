/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:54:47 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/24 15:52:27 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

void	ft_puterror(char *target, char *message)
{
	write(STDERR_FILENO, PGM_NAME, ft_strlen(PGM_NAME));
	write(STDERR_FILENO, ": ", 2);
	if (target)
	{
		write(STDERR_FILENO, target, ft_strlen(target));
		write(STDERR_FILENO, ": ", 2);
	}
	if (!message)
	{
		message = strerror(errno);
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		write(STDERR_FILENO, message, ft_strlen(message));
}

int	ft_puterror_ret(char *target, char *message, int ret)
{
	ft_puterror(target, message);
	return (ret);
}

void	ft_puterror_exit(char *target, char *message, int status)
{
	ft_puterror(target, message);
	exit(status);
}
