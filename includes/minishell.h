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
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define PATH_MAX			4096

typedef struct dirent	*t_dirent;

typedef struct		s_env{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd{
	char			**listcmd;
	struct s_cmd	*next;
}					t_cmd;


/*  dispatchjob.c       */
void				doTheJob(t_env **env, char **cmd, char **tabenv);
void				intothefork(char *path, char **cmd, char **tabenv);
void				fathersup(pid_t father, int status);

/*  commandLineAction.c */
void				printPrompt(t_env *env);
void				readCommandLine(t_cmd **base);
char 				**parseCmd(char *cmd);
char				**setTab(char *cmd);
char				*malloc_tab(char *cmd, int pos);

t_cmd				*initlcmd(void);
void				addlmaillon(char **cmd, t_cmd **liste);



/*  defineEnv.c        */
t_env				*getlocalenv(char *const envp[]);
void				setlocalenv(char *const envp[], t_env **liste);
t_env				*fillenv(t_env *newmaillon, char *fullEnv);
t_env				*initmaillon(void);
void				addmaillon(char *name, char *value, t_env **liste);
void				fillenvstep(t_env *newmaillon, int equal, int ptr, int i, char * fullenv);

/*  builtins.c        */
int					isBuiltins(char **cmd);
void				execBultins(char **cmd, t_env **env);
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
void				ft_cdaction(t_env **env, char **cmd, char *home, char *pwd);

/*	pathexec.c      */
char				*iscommande(t_env **env, char **cmd);
char				*islocalexec(char **cmd);
char				*setpath(char **tab_path, char *cmd);

/*  error.c        */
void				invalidParam(char **cmd);
void				setenvError(char **cmd);
void				ft_notfound(char *cmd);

/* listintab.c     */
void				ft_listintab(t_env	**env, char **tabenv);

/* tools.c        */
char				*ft_getlistevalue(t_env	**env, char *name);
char				**setdefaultpath(void);
t_env				*setdefaultenv(void);
char				**getdefaultenv(void);
void				setshlvl(char **tabenv);
void				setlistlvl(t_env **env);
int 				checkifonlyspace(char *value);

/* main.c*/
void			freebase(t_cmd	**base);
void			freenv(t_env	*env);
char			**settabenv(t_env *env);

#endif
