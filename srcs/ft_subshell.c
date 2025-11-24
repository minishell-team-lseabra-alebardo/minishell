/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:46:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/24 18:35:17 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_remove_parentheses(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		ft_memmove(&line[i], &line[i + 1], 1);
		i++;
	}
	i = 0;
	while (line[i])
		i++;
	line[i - 1] = 0;
}

int	ft_subshell(char **argv, char **envp)
{
	t_data	*dt;
	int		status;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		return (EXIT_FAILURE);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		return (EXIT_FAILURE);
	dt->lst_stat = ft_atoi(argv[2]);
	dt->pexit = 0;
	dt->line = ft_strdup(argv[1]);
	if (dt->line[0] == '(')
		ft_remove_parentheses(dt->line);
	ft_args_treatment(&dt->line, dt->ms_envp, 0);
	dt->split_line = ft_split_prompt(dt->line, WS_POSIX);
	ft_parser(dt);
	ft_exec_line(dt);
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt->prompt, dt->line);
	ft_cleanup_line(dt);
	status = dt->lst_stat;
	free(dt);
	return (status);
}

static char	*ft_get_ms_path(char **ms_envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(ms_envp[i], "MS_PATH=", 8))
		i++;
	return (ms_envp[i] + 8);
}

static char	**ft_include_subshell(char **args, int lst_stat)
{
	char	**new_args;

	new_args = (char **) ft_calloc(4, sizeof(char *));
	new_args[0] = ft_strdup("minishell");
	new_args[1] = args[0];
	new_args[2] = ft_itoa(lst_stat);
	free(args);
	return (new_args);
}

int	ft_prep_subshell(char **ms_envp, t_cmd *cmd, char **path, int lst_stat)
{
	if (!ft_strncmp(cmd->args[0], "minishell", 10))
	{
		*path = ft_strdup(ft_get_ms_path(ms_envp));
		return (1);
	}
	if (cmd->args[0][0] == '(')
	{
		cmd->args = ft_include_subshell(cmd->args, lst_stat);
		*path = ft_strdup(ft_get_ms_path(ms_envp));
		return (1);
	}
	return (0);
}
