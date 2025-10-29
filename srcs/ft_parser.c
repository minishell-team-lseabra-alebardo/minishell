/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/29 18:50:05 by lseabra-         ###   ########.fr       */
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

static bool	ft_is_strline_equal(char *str, char *line)
{
	size_t	len;

	if (ft_strlen(str) > (ft_linelen(line) - 1))
		len = ft_strlen(str);
	else
		len = (ft_linelen(line) - 1);
	if (ft_strncmp(str, line, len) == 0)
		return (true);
	else
		return (false);
}

static int	ft_exec_heredoc(char *limiter)
{
	char	*line;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		perror("pipe");
		return (-1);
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
		else if (ft_is_strline_equal(limiter, line))
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

void	ft_init_redir(t_cmd *cmd, char ***s_arr, char *redir)
{
	t_redir	*new_redir;
	t_redir	*cur_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return ;
	if (ft_isdigit(*redir))
	{
		new_redir->fd_from = ft_atoi(redir);
		while (ft_isdigit(*redir))
			redir++;
	}
	new_redir->type = redir;
	if (ft_is_op(new_redir->type, CMD_HEREDOC))
		new_redir->fd_to = ft_exec_heredoc(*(++*s_arr));
	else
		new_redir->filename = *(++*s_arr);
	*s_arr += 1;
	cur_redir = cmd->redir_ll;
	while (cmd->redir_ll && cmd->redir_ll->next)
		cur_redir = cmd->redir_ll->next;
	if (!cur_redir)
		cmd->redir_ll = new_redir;
	else
		cur_redir->next = new_redir;
}

t_cmd	*ft_init_cmd(char ***split_arr, t_cmd *prev, t_data *dt)
{
	t_cmd	*cur;
	int		pipefd[2];

	if (!split_arr || !*split_arr || !dt)
		return (NULL);
	cur = ft_calloc(1, sizeof(t_cmd));
	if (!cur)
		return (NULL);
	cur->ms_envp = dt->ms_envp;
	cur->lst_stat = &dt->lst_stat;
	cur->infile = STDIN_FILENO;
	cur->outfile = STDOUT_FILENO;
	if (ft_is_logic_or_pipe_op(**split_arr))
	{
		cur->prev_op = **split_arr;
		*split_arr += 1;
	}
	if (prev && !ft_strncmp(cur->prev_op, CMD_PIPE, ft_strlen(CMD_PIPE) + 1))
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe");
			return (NULL);
		}
		prev->outfile = pipefd[1];
		cur->infile = pipefd[0];
	}
	while (**split_arr)
	{
		if (ft_is_logic_or_pipe_op(**split_arr))
			break ;
		else if (ft_is_redir_op(**split_arr))
			ft_init_redir(cur, split_arr, **split_arr);
		else
		{
			ft_add_arg(cur, **split_arr);
			*split_arr += 1;
		}
	}
	return (cur);
}

void	ft_parser(t_data *dt)
{
	char	**split_tmp;
	t_cmd	*cur;

	split_tmp = dt->split_line;
	cur = NULL;
	while (split_tmp && *split_tmp)
	{
		if (!dt->list && !cur)
		{
			cur = ft_init_cmd(&split_tmp, cur, dt);
			dt->list = cur;
		}
		else
		{
			cur->next = ft_init_cmd(&split_tmp, cur, dt);
			cur = cur->next;
		}
	}
}
