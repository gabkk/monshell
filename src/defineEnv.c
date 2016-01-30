#include "minishell.h"

t_env			*getlocalenv(char *const envp[])
{
	t_env		*liste;

	if (!(envp))
		return (NULL);
	liste = NULL;
	setlocalenv(envp, &liste);
	return (liste);
}

void			setlocalenv(char *const envp[], t_env **liste)
{
	t_env		*newmaillon;
	t_env		*ptrmaillon;
	int 		i;

	i = 0;
	while (envp[i] != NULL)
	{
		newmaillon = initmaillon();
		if (!(*liste))
			*liste = newmaillon;
		ptrmaillon = *liste;
		while (ptrmaillon->next)
			ptrmaillon = ptrmaillon->next;
		ptrmaillon->next = newmaillon;
		newmaillon = fillenv(newmaillon, envp[i]);
		newmaillon->next = NULL;
		i++;
	}
}

t_env *fillenv(t_env *newmaillon, char *fullenv)
{
	int i;
	int ptr;
	int equal;
	int len;

	i = 0;
	ptr = 0;
	equal = 0;
	len = ft_strlen(fullenv);
	newmaillon->name = (char*)malloc(sizeof(char)*len);
	newmaillon->value = (char*)malloc(sizeof(char)*len);
	fillenvstep(newmaillon, equal, ptr, i, fullenv);
	return (newmaillon);
}

void		fillenvstep(t_env *newmaillon, int equal, int ptr, int i, char * fullenv)
{
	while (fullenv[i] != '\0')
	{
		if (equal == 0)
		{
			if (fullenv[i] != '=')
				newmaillon->name[ptr] = fullenv[i];
			else
			{
				equal = 1;
				newmaillon->name[ptr] = '\0';
				ptr = -1;
			}
		}
		else
			newmaillon->value[ptr] = fullenv[i];
		ptr++;
		i++;
	}
	newmaillon->value[ptr] = '\0';
}

void		addmaillon(char *name, char *value, t_env **liste)
{
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
	newmaillon->next = NULL;
}



t_env	*initmaillon(void)
{
	t_env	*initmaillon;

	initmaillon = (t_env *)malloc(sizeof(t_env));
	if (!(initmaillon))
		return (NULL);
	initmaillon->name = NULL;
	initmaillon->value = NULL;
	initmaillon->next = NULL;
	return (initmaillon);
}
