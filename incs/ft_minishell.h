/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:44:19 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/14 12:09:23 by lseabra-         ###   ########.fr       */
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
# include <ft_skips.h>
# include <ft_checks.h>
# include <ft_expand.h>
# include <stdbool.h>
# include <sys/wait.h>

int		ft_listener(void);
void	ft_read_line(t_data *dt);
char	*ft_get_ps1(void);
void	ft_parser(t_data *dt);
void	ft_search_single_quotes(char *arg);
void	ft_search_double_quotes(char *arg);
void	ft_args_treatment(char **args, char **ms_envp, int mode);
int		ft_ms_path(t_data *dt);
bool	ft_is_op(const char *s, const char *op);
bool	ft_is_logic_or_pipe_op(char *str);
bool	ft_is_redir_op(char *str);
int		ft_get_op_len(const char *s);
size_t	ft_quote_len(const char *s);
size_t	ft_parenthesis_len(const char *s);
char	**ft_free_strarr_until(char **arr, size_t position);
char	**ft_split_prompt(const char *s, char *seps);
char	**ft_strarr_dup(char **strarr);
void	ft_apply_redirs(t_cmd *cmd);
void	ft_exec_line(t_data *dt);
void	ft_dup2_close(int oldfd, int newfd);
void	ft_puterror_exit(char *target, char *message, int status);
void	ft_close_unused_fds(t_cmd *cmd);
void	ft_close_cmd_files(t_cmd *cmd);
int		ft_resolve_cmd_path(char *cmd, char **path_addr);
void	ft_wait_all_pids(t_data *dt);
void	ft_free_strarr(char **strarr);
void	ft_cleanup_line(t_data *dt);
#endif