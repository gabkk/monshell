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

# define ANSI_COLOR_YELLOW  	"\x1b[33m"
# define ANSI_COLOR_RESET   	"\x1b[0m"
# define ANSI_COLOR_LIGHT_BLUE	"\033[94m"
# define ANSI_UNDERLINE			"\x1b[4m"
# define PATH_MAX				4096
# define TTY_PATH				1025

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

typedef struct			s_hist{
	char				*cmd;
	struct s_hist		*next;
}						t_hist;

int						g_flagsignal;

/*
** dispatchjob.c
*/
void					mainbody(t_env *env);
void					dispatch(t_env **env, char **c, t_hist **h, t_cmd **b);
char					**settabenv(t_env **env);
void					into_fork(char *path, char **cmd, char **tabenv);
void					fathersup(pid_t father, int status);

/*
** display_prompt.c
*/
void					print_prompt(t_env *env);
void					print_intro(void);
void					topbar_path(char *home, int flag, char *pwd);
void					topbar_user(char *value);
void					topbar_icone(int flag);

/*
** cla.c
*/
void					read_command_line(t_cmd **base, t_hist **history);
void					addlmaillon(char **cmd, t_cmd **liste);
void					parse_value(char *value, char **tmp, t_cmd **base);

/*
** alloc_tab.c
*/
char					**parse_cmd(char *cmd);
char					**set_tab(char *cmd);
char					*malloc_tab(char *cmd, int pos);
void					fill_cmd_tab(char *cmdvalue, char **cmdtab);
void					ft_listintab(t_env	**env, char **tabenv);

/*
** defineEnv.c
*/
t_env					*getlocalenv(char *const envp[]);
void					setlocalenv(char *const envp[], t_env **liste);
void					fill_env(t_env *newmaillon, char *fullenv, int equal);
t_env					*initmaillon(void);
void					addmaillon(char *name, char *value, t_env **liste);

/*
** builtins.c
*/
int						b_check(char **c, t_env **env, t_hist **h, t_cmd **b);
void					b_exec(char **c, t_env **env, t_hist **h, t_cmd **b);
void					showenv(t_env **env);

/*
** setenv.c
*/
void					add_env(t_env **env, char **cmd);
void					setnoequal(t_env **env, char **cmd);
int						withequal(char *str);
void					setequal(t_env **env, char **cmd);
int						setenv_twocmd(t_env **env, char **cmd);

/*
** unsetenv.c
*/
void					unset_env(t_env **env, char **cmd);
void					freebase(t_cmd	**base);
void					freenv(t_env	*env);
void					unset_env_first(t_env *ptm, t_env *prev, char *cmd);

/*
** chdir.c
*/
char					*set_pwd(t_env **env, char *cmd, char *pwd, char *np);
char					*setmallocpwd(char *cmd, char *home, char *pwd);
void					ft_opendir(t_env **env, char **cmd);
void					cd_cmd(t_env **env, char **cmd, char *home, char *pwd);
void					open_n_save(t_env **env, char *pwd, char *nextpwd);

/*
** pathexec.c
*/
char					*iscommande(t_env **env, char **cmd);
int						islocalexec(char *cmd);
char					*setpath(char **tab_path, char *cmd);
char					*path_fill(DIR *directory, char *cmd, char *tab_path);
char					**setdefaultpath(void);

/*
** history.c
*/
void					add_to_history(char *cmd, t_hist **history);
void					show_history(t_hist **history);
t_hist					*inithist(void);

/*
** error.c
*/
void					invalid_param(char **cmd);
void					setenv_error(char **cmd);
void					notfound_error(char *cmd);
void					setequal_error();
char					*oldpwd_error();

/*
** tools.c
*/
char					*getlistevalue(t_env	**env, char *name);
t_env					*setdefaultenv(void);
char					**getdefaultenv(void);
void					randcol_ansi(int i);
void					ft_exit(t_env **env, t_hist **h, t_cmd **b);

/*
** tools2.c
*/
void					env_new(t_env **env, char *cmd1, char *cmd2);
void					setenv_maillon(char *pwd, char *nextpwd, t_env *ptm);
int						checkifonlyspace(char *value);
void					sig_handler(int signo);
void					setlistlvl(t_env **env);

#endif
