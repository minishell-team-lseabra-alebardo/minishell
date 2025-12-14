/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:27:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/14 17:14:55 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_init_pwd(t_data *dt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_set_env(dt, "PWD", pwd);
	free(pwd);
}

t_data	*ft_data_init(char **envp)
{
	t_data	*dt;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	ft_init_pwd(dt);
	dt->last_status = ft_get_status(0, false);
	dt->prompt = NULL;
	dt->line = NULL;
	dt->cmd_ll = NULL;
	dt->pexit = 1;
	if (ft_shlvl(dt) < 0)
		ft_close_error(dt);
	return (dt);
}
