/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:18:47 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/11 21:02:39 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPAND_H
# define FT_EXPAND_H

int		ft_is_whitespace(char c);
int		ft_avoid_quotes(char *arg, char quote, int i);
int		ft_var_size(char *arg);
void	ft_copy_var_name(char *arg, char *var_name);
int		ft_copy_start(char *new_arg, char *arg);
void	ft_variables(char **args, char **ms_envp);

#endif