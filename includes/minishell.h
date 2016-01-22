/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkuma <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 04:17:29 by gkuma             #+#    #+#             */
/*   Updated: 2016/01/16 05:11:08 by gkuma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_env{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void		doTheJob(t_env *env, char **cmd);


void				printPrompt(t_env *env);
char				**readCommandLine();
char 				**parseCmd(char *cmd);
char				**setTab(char *cmd);

t_env				*getLocalEnv(char *const envp[]);
void				setLocalEnv(char *const envp[], t_env **liste);
t_env 				*fillEnv(t_env *newmaillon, char *fullEnv);
t_env				*initEnv(void);

int					isBuiltins(char **cmd);
void				execBultins(char **cmd, t_env **env);
void				execenv(t_env **env);
void				addEnv(t_env **env, char **cmd);

#endif