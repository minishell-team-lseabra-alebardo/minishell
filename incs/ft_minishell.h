/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:44:19 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/22 14:19:45 by lseabra-         ###   ########.fr       */
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
# include <ft_macros.h>
# include <ft_types.h>

int		ft_listener(void);
void	ft_read_line(char **ms_envp);
char	*ft_get_ps1(void);
void	ft_parser(char *line);
int		ft_check_unclosed(char *line);
int		ft_check_commands(char *line);
int		ft_isop(const char *s);
size_t	ft_quote_len(const char *s);
size_t	ft_parenthesis_len(const char *s);
char	**ft_free_strarr(char **arr, size_t position);
char	**ft_split_prompt(const char *s, char *seps);
char	**ft_strarr_dup(char **strarr);

#endif