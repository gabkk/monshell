#include "minishell.h"

char		*ft_getlistevalue(t_env	**env, char *name)
{
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, name) == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

char		**setdefaultpath()
{
	char	**pathtmp;

	pathtmp = (char **)malloc(sizeof(char *) * 3);
	pathtmp[0] = "/bin";
	pathtmp[1] = "/usr/bin";
	pathtmp[2] = NULL;
	return (pathtmp);
}

char		**getdefaultenv()
{
	char	**defaultenv;
	char	tmp[PATH_MAX];

	defaultenv = (char **)malloc(sizeof(char *) * 9);
	defaultenv[0] = ft_strdup("HOSTTYPE=unknown");
	defaultenv[1] = ft_strdup("VENDOR=apple");
	defaultenv[2] = ft_strdup("OSTYPE=darwin");
	defaultenv[3] = ft_strdup("MACHTYPE=x86_64");
	defaultenv[4] = ft_strdup("SHLVL=1");
	defaultenv[5] = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	defaultenv[6] = ft_strdup("LOGNAME=default");
	defaultenv[7] = ft_strdup("USER=default");
	defaultenv[8] = NULL;
	return (defaultenv);
}

t_env		*setdefaultenv()
{
	t_env	*liste;
	char	**defaultenv;
	char	**tmp;
	int 	i;

	i = 0;
	defaultenv = getdefaultenv();
	liste = NULL;
	while (defaultenv[i] != NULL)
	{
		tmp = ft_strsplit(defaultenv[i], '=');
		addmaillon(tmp[0], tmp[1], &liste);
		ft_freetab(tmp);
		i++;
	}
	free(defaultenv[5]);
	free(defaultenv);
	return (liste);
}


void		setlistlvl(t_env **env)
{
	t_env	*ptrmaillon;
	char	*tmp;
	int		i;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "SHLVL") == 0)
		{
			i = ft_atoi(ptrmaillon->value) + 1;
			tmp = ft_itoa(i);
			free(ptrmaillon->value);
			ptrmaillon->value = ft_strdup(tmp); // a free
			free(tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
}

int			checkifonlyspace(char *value)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (ft_isspace(value[i]) == 1)
			j++;
		i++;
	}
	if (i == j)
		return(1);
	return 0;
}

void sig_handler(int signo)
{
  	if (signo == SIGINT)
  	{
    	//signal(SIGCONT, sig_handler);
//     	signal(SIGINT, SIG_DFL);
//     	raise(SIGINT);
//  	signal(SIGINT, SIG_IGN);
//      write(0,"\n", 1);
//   	mainbody(env);
//  		ft_putnbr(mainsignal);
  		if (flagsignal != 0)
  		{
  			kill(flagsignal, SIGKILL);
  			write(1,"\n",1);
  			flagsignal = 0;
 // 			signal(SIGINT, SIG_DFL);
  		}
  		//if (mainsignal == 0)
  			//signal(SIGINT, SIG_DFL);
  		return;
  	}
  		
	// else if (signo == SIGKILL)
	//     ft_putendl("received SIGKILL");
	// else if (signo == SIGSTOP)
 //    	ft_putendl("received SIGSTOP");
}





















