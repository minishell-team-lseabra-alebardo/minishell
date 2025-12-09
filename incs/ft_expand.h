/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:18:47 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/09 14:53:04 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPAND_H
# define FT_EXPAND_H

int		ft_is_whitespace(char c);
int		ft_avoid_quotes(char *arg, char quote, int i);
int		ft_var_size(char *arg);
void	ft_copy_var_name(char *arg, char *var_name);
int		ft_copy_start(char *new_arg, char *arg, int i);
void	ft_copy_rest(char *new_arg, char *src);
char	*ft_expand_variable(char **ms_envp, t_data *dt, char *arg, int *i);
char	*ft_prep_lst_stat(char *arg);
char	*ft_copy_lst_stat(int lst_stat, char *arg, int *i);

#endif