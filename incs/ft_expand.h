/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:18:47 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/02 17:12:28 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPAND_H
# define FT_EXPAND_H

int		ft_is_whitespace(char c);
int		ft_avoid_quotes(char *arg, char quote, int i);
int		ft_var_size(char *arg);
void	ft_copy_var_name(char *arg, char *var_name);
int		ft_copy_start(char *new_arg, char *arg, int i);
char	*ft_expand_variable(t_data *dt, char **ms_envp, char *arg, int *i);

#endif