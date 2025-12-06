/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:46:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/05 23:18:44 by alebarbo         ###   ########.fr       */
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

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	ft_get_status(ft_atoi(argv[2]), true);
	dt->pexit = 0;
	dt->line = ft_strdup(argv[1]);
	if (dt->line[0] == '(')
		ft_remove_parentheses(dt->line);
	ft_args_treatment(&dt->line, dt, 0);
	dt->split_line = ft_split_prompt(dt->line, WS_POSIX);
	ft_parser(dt);
	ft_exec_line(dt);
	return (ft_exit(dt, NULL));
}

static char	*ft_get_ms_path(char **ms_envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(ms_envp[i], "MS_PATH=", 8))
	{
		i++;
		if (!ms_envp[i])
			return (0);
	}
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
	char	*ms_path;

	ms_path = ft_get_ms_path(ms_envp);
	if (!ms_path)
		return (0);
	if (!ft_strncmp(cmd->args[0], "minishell", 10))
	{
		*path = ft_strdup(ms_path);
		return (1);
	}
	if (cmd->args[0][0] == '(')
	{
		cmd->args = ft_include_subshell(cmd->args, lst_stat);
		*path = ft_strdup(ms_path);
		return (1);
	}
	return (0);
}
