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
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>

# define ANSI_COLOR_YELLOW  	"\x1b[33m"
# define ANSI_COLOR_RESET   	"\x1b[0m"
# define ANSI_COLOR_LIGHT_BLUE	"\033[94m"
# define ANSI_UNDERLINE			"\x1b[4m"
# define PATH_MAX				4096
# define TTY_PATH				1025
# define PATH_HIST2				"/nfs/2014/g/gkuma/.mshell_hist"
# define PATH_HIST				"/home/shinja/.mshell_hist"

typedef struct dirent	*t_dirent;

typedef struct 			s_term{
	int					action;
	int					canon;
	int					echo;
	int					vim;
	int					tim;
	int					size[2];
}						t_term;

typedef struct			s_input{
	char				c;
	int					index;
	int					pos[2];
	int					selected;
	struct s_input		*prev;
	struct s_input		*next;
}						t_input;

typedef struct			s_env{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_cursor{
	int					posx;
	int					posy;
	int					ymax;
	struct s_cursor		*next;
	struct s_cursor		*prev;
}						t_cursor;

typedef struct			s_para{
	int					fd;
	int					current_l;
	int					total_h;
	int					current_h;
	int					selector;
	int					total_c;
	int					prompt_s;
	char				*cmd;
	struct s_cursor		*cursor;
	struct s_env		*env;
	struct s_term		*term;
	struct s_input		*copy;
}						t_para;

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
** maillon_op.c
*/
t_env					*initmaillon(void);
void					addmaillon(char *name, char *value, t_env **liste);
void					setenv_maillon(char *pwd, char *nextpwd, t_env *ptm);
void					add_maillon_cmd(char **cmd, t_cmd **liste);

/*
** main_body.c
*/
void					mainbody(t_para *glob);
void					main_loop(t_para *glob);
void					main_action(t_para **glob);
void					parse_value(t_para **glob, t_cmd **base);

/*
** dispatchjob.c
*/
void					mainbody(t_para *glob);
void					dispatch(t_env **env, char **c);
void					into_fork(char *path, char **cmd, char **tabenv);
void					fathersup(pid_t father, int status);

/*
** display_prompt.c
*/
void					print_prompt(t_para **glob);
void					print_intro(int fd);
int						topbar_path(char *home, int flag, char *pwd);
int						topbar_user(int fd, char *value);
void					topbar_icone(int fd);

/*
** read_input.c
*/
void					read_arrow(t_para **glob, t_input **input);
void					read_input(t_para *glob, t_input **input);
void					read_if_print(t_para **glob, t_input **input, char buff);
void					read_ud(t_para **glob, t_input **input, char buff);
void					read_lr(t_para **glob, t_input **input, char buff);

/*
** alloc_tab.c
*/
char					**parse_cmd(char *cmd);
char					**set_tab(char *cmd);
char					*malloc_tab(char *cmd, int pos);
void					fill_cmd_tab(char *cmdvalue, char **cmdtab);
void					ft_listintab(t_env	**env, char **tabenv);

/*
** define_env.c
*/
t_env					*getlocalenv(char *const envp[]);
void					setlocalenv(char *const envp[], t_env **liste);
void					fill_env(t_env *newmaillon, char *fullenv, int equal);
char					**settabenv(t_env **env);

/*
** builtins.c
*/
int						b_check(char **c, t_env **env);
void					b_exec(char **c, t_env **env);
void					showenv(t_env **env);
int						isexec(char *cmd, t_env **env);

/*
** setenv.c
*/
void					env_new(t_env **env, char *cmd1, char *cmd2);
void					add_env(t_env **env, char **cmd);
void					setnoequal(t_env **env, char **cmd);
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
** cd.c
*/
char					*set_pwd(t_env **env, char *cmd, char *pwd, char *np);
char					*setmallocpwd(char *cmd, char *home, char *pwd);
void					ft_opendir(t_env **env, char **cmd);
void					cd_cmd(t_env **env, char **cmd, char *home, char *pwd);
void					open_n_save(t_env **env, char *pwd, char *nextpwd);

/*
** pathexec.c
*/
char					*iscommande(t_env **env, char *cmd);
int						islocalexec(char *cmd);
char					*setpath(char **tab_path, char *cmd);
char					*path_fill(DIR *directory, char *cmd, char *tab_path);
char					**setdefaultpath(void);

/*
** history.c
*/
void					add_to_history(char *cmd);
void					set_hist(t_hist **history, char *line);
void					show_history(void);
t_hist					*inithist(void);
void					freehist(t_hist *newhist);

/*
** termcaps_history.c
*/
void					show_last_hist(t_para **glob, t_input **input);
void					tot_hist(t_para **glob);

/*
** error.c
*/
void					invalid_param(char **cmd);
void					setenv_error(char **cmd);
void					notfound_error(char *cmd);
void					setequal_error();
char					*oldpwd_error();

/*
** default_env.c
*/
t_env					*setdefaultenv(void);
char					**getdefaultenv(void);

/*
** signal.c
*/
void					sig_handler(int signo);

/*
** exit.c
*/
void					ft_exit(void);

/*
** termcaps.c
*/
void					set_term_param(t_para *glob);
void					check_terminal(t_para *glob);
void					init_term(t_para *glob);
void					winsize(int fd, int i[2]);

/*
** lst_input_op.c
*/
t_input					*init_lst_input();
void					print_lst_input(t_input **input, t_para **glob);
void					save_cmd(t_input **input, t_para **glob);
void					delete_lst_input(t_input **input);
void					add_back_input(t_input **input, char buf, int i);
void					set_first_input(t_input **input, char buf, int i);
void					add_inside_input(t_input **input, char buf, int i);

/*
** backspace.c
*/
void					backspace(t_input **input, t_para **glob);
void					backspace_last(t_input **input, t_para **glob);
void					backspace_inside(t_input **input, t_para **glob);

/*
** selector.c
*/
void					mode_selector(t_para **glob);
void					set_selector(t_para **glob, t_input **input, int index, int direction);
void					selector_action(t_para **glob, t_input **input, int buff);
void					selector_copy(t_para **glob, t_input **input);
void					selector_cut(t_para **glob, t_input **input);
void					selector_paste(t_para **glob, t_input **input);

/*
** cursor.c
*/
t_cursor				*init_cursor(void);
void					add_cursor(t_cursor **cursor);
void					freecursor(t_cursor **cursor);
void					cursor_pos_init(t_para **glob);

/*
** tools.c
*/
char					*getlistevalue(t_env	**env, char *name);
void					randcol_ansi(int i);
int						checkifonlyspace(char *value);
void					setlistlvl(t_env **env);
void					clear_line(t_para **glob, t_input **input);

/*
** tool2.c
*/

void					modify_ymax_to_last(t_para **glob, t_cursor **cursor, int value);

/*
** backspace_op.c
*/
void					back_del_maillon(t_para **glob, t_input **input);
void					back_redraw(t_para **glob, t_input **input);
void					back_reposition(t_para **glob, int x, int y);

#endif


