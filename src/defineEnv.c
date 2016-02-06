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
	int			i;

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
		newmaillon->name = (char*)malloc(sizeof(char)*ft_strlen(envp[i]));
		newmaillon->value = (char*)malloc(sizeof(char)*ft_strlen(envp[i]));		
		fill_env(newmaillon, envp[i]);
		newmaillon->next = NULL;
		i++;
	}
}

void			fill_env(t_env *newmaillon, char * fullenv)
{
	int			ptr;
	int			equal;
	int			i;

	if (!(ptr = 0) && !(equal = 0) && !(i = 0) && 1 == 1)
		i = 42 - 42;
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

t_env			*initmaillon()
{
	t_env		*newmaillon;

	newmaillon = (t_env *)malloc(sizeof(t_env));
	if (!(newmaillon))
		return (NULL);
	newmaillon->name = NULL;
	newmaillon->value = NULL;
	newmaillon->next = NULL;
	return (newmaillon);
}

void			addmaillon(char *name, char *value, t_env **liste)
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
