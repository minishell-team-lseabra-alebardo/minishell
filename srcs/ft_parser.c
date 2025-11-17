/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:51 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/17 14:53:39 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static char	*ft_get_str_fd(char *redir)
{
	size_t	i;
	char	*str_fd;

	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	str_fd = ft_substr(redir, 0, i);
	return (str_fd);
}

static void	ft_init_redir(t_cmd *cmd, char ***s_arr, char *redir)
{
	t_redir	*new_redir;
	t_redir	*cur_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return ;
	if (ft_isdigit(*redir))
	{
		new_redir->fd_from = ft_get_str_fd(redir);
		while (ft_isdigit(*redir))
			redir++;
	}
	new_redir->type = redir;
	if (ft_is_op(new_redir->type, CMD_HEREDOC))
		new_redir->fd_to = ft_exec_heredoc(*(++*s_arr));
	else
		new_redir->filename = *(++*s_arr);
	*s_arr += 1;
	while (cmd->redir_ll && cmd->redir_ll->next)
		cmd->redir_ll = cmd->redir_ll->next;
	cur_redir = cmd->redir_ll;
	if (!cur_redir)
		cmd->redir_ll = new_redir;
	else
		cur_redir->next = new_redir;
}

static void	ft_parse_cmd_tokens(char ***split_arr, t_cmd *cmd)
{
	while (**split_arr)
	{
		if (ft_is_logic_or_pipe_op(**split_arr))
			break ;
		else if (ft_is_redir_op(**split_arr))
			ft_init_redir(cmd, split_arr, **split_arr);
		else
		{
			ft_add_arg(cmd, **split_arr);
			*split_arr += 1;
		}
	}
}

static t_cmd	*ft_init_cmd(char ***split_arr, t_cmd *prev, t_data *dt)
{
	t_cmd	*cur;

	if (!split_arr || !*split_arr || !dt)
		return (NULL);
	cur = ft_calloc(1, sizeof(t_cmd));
	if (!cur)
		return (NULL);
	cur->ms_envp = dt->ms_envp;
	cur->infile = STDIN_FILENO;
	cur->outfile = STDOUT_FILENO;
	if (ft_is_logic_or_pipe_op(**split_arr))
	{
		cur->prev_op = **split_arr;
		*split_arr += 1;
	}
	if (prev && ft_is_op(cur->prev_op, CMD_PIPE))
	{
		if (ft_init_pipe(cur, prev) < 0)
			return (NULL);
	}
	ft_parse_cmd_tokens(split_arr, cur);
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
		if (!dt->cmd_ll && !cur)
		{
			cur = ft_init_cmd(&split_tmp, cur, dt);
			dt->cmd_ll = cur;
		}
		else
		{
			cur->next = ft_init_cmd(&split_tmp, cur, dt);
			cur = cur->next;
		}
	}
}
