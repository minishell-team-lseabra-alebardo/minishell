/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 04:18:39 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/07 04:28:26 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WILDCARDS_H
# define FT_WILDCARDS_H

int		ft_count_names(void);
char	**ft_get_names(int names_count);
char	*ft_check_match(char *match);
char	*ft_match_ends(char **split, char *name, int *wildmark);
void	ft_match_middle(char **split, char *temp, int *wildmark, int *i);
int		ft_search_matches(char **split, char *name, int *wildmark);
int		ft_avoid_parentheses(char *line, int i);
void	ft_move_wildchars(char *wildtoken);
int		ft_copy_wildstart(char *new_arg, char *arg, int i);
char	*ft_search_wildquotes(char *wildtoken);
int		ft_search_wildcard(char *line, int *wildmark, int start);
char	*ft_wildcards(char *line);

#endif