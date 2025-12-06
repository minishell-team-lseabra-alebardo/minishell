/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:33:46 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/06 15:32:26 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static bool	ft_is_limiter(char *lim, char *line)
{
	size_t	len;

	if (ft_strlen(lim) > (ft_linelen(line) - 1))
		len = ft_strlen(lim);
	else
		len = (ft_linelen(line) - 1);
	if (ft_strncmp(lim, line, len) == 0)
		return (true);
	else
		return (false);
}

static int	ft_perror_return_status(char *target, int status)
{
	perror(target);
	return (status);
}

int	ft_exec_heredoc(char *lim)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		return (ft_perror_return_status("pipe", ERROR));
	while (true)
	{
		ft_putstr_fd(HEREDOC_PREFIX, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_printf("\n%s: %s (wanted `%s')\n", PGM_NAME, HEREDOC_WARN, lim);
			break ;
		}
		else if (ft_is_limiter(lim, line))
			break ;
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	ft_add_arg(t_cmd *cmd, char *new_arg)
{
	int		size;
	char	**new_arr;

	if (!cmd->args)
	{
		cmd->args = ft_calloc(2, sizeof(char *));
		cmd->args[0] = new_arg;
	}
	else
	{
		size = 0;
		while (cmd->args[size])
			size++;
		new_arr = ft_calloc(size + 2, sizeof(char *));
		if (!new_arr)
			return ;
		ft_memcpy(new_arr, cmd->args, size * sizeof(cmd->args));
		free(cmd->args);
		new_arr[size] = new_arg;
		cmd->args = new_arr;
	}
}

int	ft_init_pipe(t_cmd *cur, t_cmd *prev)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (ERROR);
	}
	prev->outfile = pipefd[1];
	cur->infile = pipefd[0];
	return (SUCCESS);
}
