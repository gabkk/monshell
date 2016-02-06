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
# include <signal.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define PATH_MAX			4096


typedef struct dirent	*t_dirent;

typedef struct			s_env{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_cmd{
	char				**listcmd;
	struct s_cmd		*next;
}						t_cmd;

int						flagsignal;

/*  dispatchjob.c       */
void					mainbody(t_env *env);
void					dispatch(t_env **env, char **cmd);
char					**settabenv(t_env **env);
void					into_fork(char *path, char **cmd, char **tabenv);
void					fathersup(pid_t father, int status);

/* display_prompt.c		*/
void					printPrompt(t_env *env);

/*  commandLineAction.c */
void					readCommandLine(t_cmd **base);
void					addlmaillon(char **cmd, t_cmd **liste);
void					parse_value(char *value, char **tmp, t_cmd **base);

/*  alloc_tab.c  		*/
char					**parse_cmd(char *cmd);
char					**setTab(char *cmd);
char					*malloc_tab(char *cmd, int pos);
void					fill_cmd_tab(char *cmdvalue,char **cmdTab);

/*  defineEnv.c        */
t_env					*getlocalenv(char *const envp[]);
void					setlocalenv(char *const envp[], t_env **liste);
void					fill_env(t_env *newmaillon, char * fullenv);
t_env					*initmaillon(void);
void					addmaillon(char *name, char *value, t_env **liste);

/*  builtins.c        */
int						builtins_check(char **cmd, t_env **env);
void					builtins_exec(char **cmd, t_env **env);
void					showenv(t_env **env);

/*  setenv.c        */
void					add_env(t_env **env, char **cmd);
void					setnoequal(t_env **env, char **cmd);
int						withequal(char *str);
void					setequal(t_env **env, char **cmd);
int						setenv_twocmd(t_env **env, char **cmd);

/*  unsetenv.c      */
void					unset_env(t_env** env, char **cmd);
void					freebase(t_cmd	**base);
void					freenv(t_env	*env);

/*  chdir.c        */
char					*set_pwd(t_env **env, char *cmd, char *home, char *pwd, char *nextpwd);
char					*ft_setmallocpwd(char *cmd, char *home, char *pwd);
void					ft_opendir(t_env **env, char **cmd);
void					cd_cmd(t_env **env, char **cmd, char *home, char *pwd);
void					open_n_save(t_env **env, char *pwd, char *nextpwd);

/*	pathexec.c      */
char					*iscommande(t_env **env, char **cmd);
char					*islocalexec(char **cmd);
char					*setpath(char **tab_path, char *cmd);
char					*path_fill(DIR *directory, char *cmd, char *tab_path);

/*  error.c        */
void					invalid_param(char **cmd);
void					setenv_error(char **cmd);
void					ft_notfound(char *cmd);
void					setequal_error();

/* tools.c        */
char					*ft_getlistevalue(t_env	**env, char *name);
char					**setdefaultpath(void);
t_env					*setdefaultenv(void);
char					**getdefaultenv(void);
void					ft_listintab(t_env	**env, char **tabenv);


/*		tools2.		c*/
void					env_new(t_env **env, char *cmd1, char *cmd2);
void					setenv_maillon(char *pwd, char *nextpwd, t_env *ptrmaillon);
int						checkifonlyspace(char *value);
void					sig_handler(int signo);
void					setlistlvl(t_env **env);

#endif
