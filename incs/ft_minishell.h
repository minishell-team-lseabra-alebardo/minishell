/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:44:19 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/16 22:42:46 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <libft.h>
# include <ft_errors.h>
# include <ft_macros.h>
# include <ft_types.h>

int		ft_listener(void);
void	ft_read_line(void);
char	*ft_get_ps1(void);
void	ft_parser(char *line);
int		ft_check_unclosed(char *line);
char	**ft_split_prompt(const char *s, char *seps);
char	**ft_strarr_dup(char **strarr);

#endif