/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:53:43 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/25 15:06:43 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	**ft_getenv(char *name, char **ms_envp)
{
	size_t	len;
	int		i;

	if (!name || !ms_envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (ms_envp[i])
	{
		if (ft_strncmp(name, ms_envp[i], len) == 0 && ms_envp[i][len] == '=')
			return (ms_envp + i);
		i++;
	}
	return (NULL);
}

void	ft_set_env(char *name, char *value, char **ms_envp)
{
	char	*res;
	char	*tmp;
	char	**env_addr;
	size_t	name_len;

	if (!name || !value || !ms_envp || !*ms_envp)
		return ;
	name_len = 0;
	env_addr = ft_getenv(name, ms_envp);
	if (!env_addr)
		return ;
	while ((*env_addr)[name_len] && (*env_addr)[name_len] != '=')
		name_len++;
	if ((*env_addr)[name_len] == '=')
		name_len++;
	else
		return ;
	tmp = ft_substr(*env_addr, 0, name_len);
	res = ft_strjoin(tmp, value);
	free(tmp);
	tmp = *env_addr;
	*env_addr = res;
	free(tmp);
}

int	ft_change_directory(t_data *dt, t_cmd *cmd)
{
	char	*pwd;
	char	*path;

	ft_close_cmd_files(cmd);
	if (!cmd->args[1])
		path = *(ft_getenv("HOME", dt->ms_envp)) + 5;
	else if (cmd->args[2])
		return (ft_puterror_ret("cd", NULL, ERR_TOO_MANY_ARGS, EXIT_FAILURE));
	else if (cmd->args[1][0] == '\0')
		return (EXIT_SUCCESS);
	else
		path = cmd->args[1];
	pwd = getcwd(0, 0);
	if (chdir(path) < 0)
	{
		free(pwd);
		ft_puterror("cd", cmd->args[1], NULL);
		return (EXIT_FAILURE);
	}
	ft_set_env("OLD_PWD", pwd, dt->ms_envp);
	free(pwd);
	pwd = getcwd(0, 0);
	ft_set_env("PWD", pwd, dt->ms_envp);
	free(pwd);
	return (EXIT_SUCCESS);
}
