/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/27 10:57:11 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static bool	ft_is_logic_or_pipe_op(char *str)
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

static bool	ft_is_redir_op(char *str)
{
	bool	res;

	res = false;
	if (ft_is_op(str, CMD_HEREDOC))
		res = true;
	else if (ft_is_op(str, CMD_IN))
		res = true;
	else if (ft_is_op(str, CMD_OUT))
		res = true;
	else if (ft_is_op(str, CMD_OUT_APPEND))
		res = true;
	return (res);
}

static void	ft_exec_heredoc(t_cmd *cur, char *limiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror(strerror(errno));
		return ;
	}
	while (true)
	{
		ft_putstr_fd(HEREDOC_PREFIX, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_printf("\n%s (wanted `%s')\n", HERE_DOC_WARNING, limiter);
			break ;
		}
		else if (is_strline_equal(limiter, line))
			break ;
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(pipefd[1]);
	cur->infile = pipefd[0];
}

void	ft_init_file(char **arr, t_cmd *cmd)
{
	if (ft_is_op(*arr, CMD_HEREDOC))
		ft_exec_heredoc(cmd, arr + 1);
	else if (ft_is_op(*arr, CMD_IN))
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		cmd->infile = open(arr + 1, O_RDONLY);
		if (cmd->infile == -1)
			cmd->error = ft_strdup(strerror(errno));
	}
	else if (ft_is_op(*arr, CMD_OUT))
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		cmd->outfile = open(arr + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->outfile == -1)
			cmd->error = ft_strdup(strerror(errno));
	}
	else if (ft_is_op(*arr, CMD_OUT_APPEND))
	{
		if (cmd->outfile > 2)
			close(cmd->outfile);
		cmd->outfile = open(arr + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->outfile == -1)
			cmd->error = ft_strdup(strerror(errno));
	}
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

t_cmd	*ft_init_cmd(char ***split_arr, t_cmd *prev, t_data *dt)
{
	t_cmd	*cur;

	if (!split_arr || !*split_arr || !dt)
		return (NULL);
	cur = ft_calloc(1, sizeof(t_cmd));
	if (!cur)
		return (NULL);
	cur->ms_envp = dt->ms_envp;
	cur->lst_stat = dt->lst_stat;
	if (ft_is_logic_or_pipe_op(**split_arr))
	{
		cur->prev_op = *split_arr;
		*split_arr++;
	}
	while (**split_arr)
	{
		if (cur->error || ft_is_logic_or_pipe_op(**split_arr))
			break ;
		else if (ft_is_redir_op(**split_arr))
		{
			ft_init_file(*split_arr, cur);
			*split_arr += 2;
		}
		else
		{
			ft_add_arg(cur, *split_arr);
			*split_arr++;
		}
	}
	return (cur);
}

void	ft_parser(t_data *dt)
{
	char	**split_tmp;
	t_data	*cur;

	split_tmp = dt->split_line;
	cur = dt->list;
	while (split_tmp && *split_tmp)
		cur = ft_init_cmd(&split_tmp, cur, dt);
}
