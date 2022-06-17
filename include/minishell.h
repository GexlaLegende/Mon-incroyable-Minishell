/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:18 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/17 18:49:47 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
	char			*cmd;
	int				*redir_type;
	char			**redir_file;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	t_list	*cmd_table;
	int		squote;
	int		dquote;
	int		r_tabl;
	char	**paths;
}	t_data;

//Lst ------------------------------------------------
t_list	*ft_lstnew(char *cmd, int *redir_type, char **redir_file);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst);
//----------------------------------------------------

//Parsing---------------------------------------------
int		ft_parsing(char *str, t_data *data);
int		ft_parsing2(char *str, t_data *data, int end);
void	ft_addpipe(t_data *data);
void	quotes_switch(t_data *data, char *str, int i);
int		redir_parsing(char *str, int i, t_data *data, int **redir_type, char ***redir_file);
int		count_redir(char *str, t_data *data);
//----------------------------------------------------

//Execution-------------------------------------------
int		ft_execution(t_data *data, char **env);
char	**fonctionkirecuplavariablepathdanslenv(char **env);
char	*recupathline(char **env);
int		exekonecmd(t_data *data);
char	**get_cmd(t_data *data);
int		get_argnbr(char *str, t_data *data);
//----------------------------------------------------

//Errors----------------------------------------------
void	parserror(int nbr);
void	exekerror(int nbr);
//----------------------------------------------------

//Utils-----------------------------------------------
char	*ft_strmjoin(char *s1, char c);
size_t	ft_strlen(char *str);
//----------------------------------------------------

#endif