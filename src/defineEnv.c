#include "minishell.h"

t_env	*getLocalEnv(char *const envp[]){
	t_env	*liste;

	if (!(envp))
		return (NULL);
	liste = NULL;
	setLocalEnv(envp, &liste);
	return (liste);
}

void	setLocalEnv(char *const envp[], t_env **liste){
	t_env	*newmaillon;
	t_env	*ptrmaillon;
	int 	i;

	i = 0;
	while (envp[i] != NULL)
	{
		newmaillon = initmaillon();
		if (!(*liste))
			*liste = newmaillon;
		ptrmaillon = *liste;
		while (ptrmaillon->next){
			ptrmaillon = ptrmaillon->next;
		}
		ptrmaillon->next = newmaillon;
		newmaillon = fillEnv(newmaillon, envp[i]);
		newmaillon->next = NULL;
		i++;
	}
}

t_env *fillEnv(t_env *newmaillon, char *fullEnv){
	int i;
	int ptr;
	int equal;
	int len;
	char *name;
	char *value;

	i = 0;
	ptr = 0;
	equal = 0;
	len = ft_strlen(fullEnv);
	name = (char*)malloc(sizeof(char)*len);
	value = (char*)malloc(sizeof(char)*len);
	while (fullEnv[i] != '\0')
	{
		if (equal == 0)
		{
			if (fullEnv[i] != '='){
				name[ptr] = fullEnv[i];
			}
			else{
				equal = 1;
				name[ptr] = '\0';
				ptr = -1;
			}
		}else{
			value[ptr] = fullEnv[i];
		}
		ptr++;
		i++;
	}
	value[ptr] = '\0';
	newmaillon->name = ft_strdup(name);
	newmaillon->value = ft_strdup(value);
	free(name);
	free(value);
	return (newmaillon);
}

t_env	*setdefaultenv(){
	t_env	*liste;
	char	**defaultenv;
	char	**tmp;
	int 	i;

	i = 0;
	defaultenv = getdefaultenv();
	//ft_ptab(defaultenv);
	//ft_putendl("");
	//ft_putendl("");
	//ft_putendl("");
	liste = NULL;
	while (defaultenv[i] != NULL)
	{
		//ft_putendl("");
		//ft_putendl(defaultenv[i]);
		//ft_putnbr(i);
		tmp = ft_strsplit(defaultenv[i], '=');
		addmaillon(tmp[0], tmp[1], &liste);
		ft_freetab(tmp);
		i++;
	}
	free(defaultenv[5]); // a checker
	free(defaultenv);
	//ft_putendl("out setdefault");
	return (liste);
}

void		addmaillon(char *name, char *value, t_env **liste){
	t_env		*newmaillon;
	t_env		*ptrmaillon;

	newmaillon = initmaillon();
	if (!(*liste))
		*liste = newmaillon;
	ptrmaillon = *liste;
	if (!(newmaillon) || !newmaillon)
		return ;
	while (ptrmaillon->next)
	{
		ptrmaillon = ptrmaillon->next;
	}
	ptrmaillon->next = newmaillon;
	newmaillon->name = ft_strdup(name);
	newmaillon->value = ft_strdup(value);
	//ft_putendl(newmaillon->name);
	//ft_putendl(newmaillon->value);
	newmaillon->next = NULL;	
}

char		**getdefaultenv(){
	char	**defaultenv;
	char	*tmp;

	defaultenv = (char **)malloc(sizeof(char *) * 9);
	defaultenv[0] = "HOSTTYPE=unknown";
	defaultenv[1] = "VENDOR=apple";
	defaultenv[2] = "OSTYPE=darwin";
	defaultenv[3] = "MACHTYPE=x86_64";
	defaultenv[4] = "SHLVL=1";
	tmp = (char *)malloc(sizeof(char) * 100); // mettre une valeur correct dans le buffer
	defaultenv[5] = ft_strjoin("PWD=", getcwd(tmp, 99));
	defaultenv[6] = "LOGNAME=default";
	defaultenv[7] = "USER=default";
	defaultenv[8] = NULL;
	free(tmp);
	return (defaultenv);
}

t_env	*initmaillon(void){
	t_env	*initmaillon;

	initmaillon = (t_env *)malloc(sizeof(t_env));
	if (!(initmaillon))
		return (NULL);
	initmaillon->name = NULL;
	initmaillon->value = NULL;
	initmaillon->next = NULL;
	return (initmaillon);
}
