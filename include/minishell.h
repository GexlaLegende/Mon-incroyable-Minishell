/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:18 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/15 15:27:02 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd_list
{
	char			*cmd;
	int				*redir_type;
	char			**redir_file;
	struct s_list	*next;
}	t_cmd_list;

typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct t_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	t_cmd_list	*cmd_table;
	t_env_list	*env_table;
	int			squote;
	int			dquote;
	int			r_tabl;
}	t_data;

//Lst ------------------------------------------------
t_cmd_list	*ft_lstnew(char *cmd, int *redir_type, char **redir_file);
void		ft_lstadd_front(t_cmd_list **alst, t_cmd_list *new);
int			ft_lstsize(t_cmd_list *lst);
t_cmd_list	*ft_lstlast(t_cmd_list *lst);
void		ft_lstadd_back(t_cmd_list **alst, t_cmd_list *new);
void		ft_lstclear(t_cmd_list **lst);
//----------------------------------------------------

//Parsing---------------------------------------------
void		parserror(int nbr);
int			ft_lexer(char *str, t_data *data);
int			ft_parser(char *str, t_data *data, int end);
void		ft_addpipe(t_data *data);
void		quotes_switch(t_data *data, char *str, int i);
int			redir_parsing(char *str, int i, t_data *data, int **redir_type, char ***redir_file);
int			count_redir(char *str, t_data *data);
//----------------------------------------------------

//Environnement---------------------------------------
int			ft_env_var(t_data *data, char **env);
//----------------------------------------------------

//Utils-----------------------------------------------
char		*ft_strmjoin(char *s1, char c);
size_t		ft_strlen(char *str);
//----------------------------------------------------

#endif