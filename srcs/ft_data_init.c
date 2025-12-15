/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:27:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 22:41:08 by alebarbo         ###   ########.fr       */
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

t_data	**ft_create_dt_arr(t_data *dt)
{
	t_data **dt_arr;

	dt_arr = (t_data **) ft_calloc(100, sizeof(t_data *));
	if (!dt_arr)
		return (0);
	dt_arr[0] = dt;
	return (dt_arr);
}

void	ft_expand_dt_arr(t_data **dt_arr, t_data *dt)
{
	int		i;

	i = 0;
	while (dt_arr[i])
		i++;
	dt_arr[i] = dt;
}

t_data	*ft_data_init(char **envp)
{
	t_data	*dt;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->subshell = 0;
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	ft_init_pwd(dt);
	dt->last_status = ft_get_status(0, false);
	dt->prompt = NULL;
	dt->line = NULL;
	dt->cmd_ll = NULL;
	if (ft_shlvl(dt) < 0)
		ft_close_error(dt);
	return (dt);
}
