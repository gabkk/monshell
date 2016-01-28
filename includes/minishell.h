/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
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
# include <dirent.h>

typedef struct dirent	*t_dirent;

typedef struct		s_env{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

void		doTheJob(t_env **env, char **cmd, char *const envp[]);

/*  commandLineAction.c */
void				printPrompt(t_env *env);
char				**readCommandLine();
char 				**parseCmd(char *cmd);
char				**setTab(char *cmd);
char				*malloc_tab(char *cmd, int pos);

/*  defineEnv.c        */
t_env				*getLocalEnv(char *const envp[]);
void				setLocalEnv(char *const envp[], t_env **liste);
t_env				*fillEnv(t_env *newmaillon, char *fullEnv);
t_env				*initmaillon(void);
t_env				*setdefaultenv(void);
char				**getdefaultenv(void);
void				addmaillon(char *name, char *value, t_env **liste);

/*  builtins.c        */
int					isBuiltins(char **cmd);
void				execBultins(char **cmd, t_env **env, int status);
void				showenv(t_env **env);

/*  setenv.c        */
void				addEnv(t_env **env, char **cmd);
void				addNewEnv(t_env **env, char **cmd);
int					isvalidvar(char *str);
void				setnoequal(t_env **env, char **cmd);
int 		 		withequal(char *str);
void				setequal(t_env **env, char **cmd);

/*  unsetenv.c      */
void				unset_env(t_env** env, char **cmd);

/*  chdir.c        */
void				ft_opendir(t_env **env, char **cmd);
void				ft_savepwd(t_env **env, char *pwd, char *nextpwd);
char		 		*ft_setpwd(t_env **env, char *cmd, char *home, char *pwd);
char				*ft_setmallocpwd(char *cmd, char *home, char *pwd);
void				ft_opennsave(t_env **env, char *pwd, char *nextpwd);

/*	pathexec.c      */
char				*iscommande(t_env **env, char **cmd, char **pathtmp);
char				*islocalexec(char **cmd);
char				*setpath(char **tab_path, char *value, char *cmd);

/*  error.c        */
void				invalidParam(char **cmd);
void				setenvError(char **cmd);
void				ft_notfound(char *cmd);

/* listintab.c     */
char 				**ft_listintab(t_env **env);

/* tools.c        */
char				*ft_getlistevalue(t_env	**env, char *name);

#endif
