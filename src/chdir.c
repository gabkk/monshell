#include "minishell.h"

void		ft_opendir(t_env **env, char **cmd){
	t_env			*ptrmaillon;
	DIR				*directory;
	char			*pwd;
	char			*tmp;
	char 			*nextpwd;
	char			*home;
	int				i;
	int				j;
	char			*tmp2;
	char			*test;

	ptrmaillon = *env;
	pwd = NULL;
	tmp = NULL;
	nextpwd = NULL;
	home = NULL;
	i = 0;
	j = 0;
	if (!cmd[1])
		cmd[1] = NULL;
	while (ptrmaillon)
	{
		if (ptrmaillon && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			//pwd = (char *)malloc(sizeof(char) * ft_strlen(ptrmaillon->value) + 1);
			pwd = ptrmaillon->value;
			break;
		}
		ptrmaillon = ptrmaillon->next;
	}
	if (pwd)
	{
		if (!cmd[1]) //fine but check leacks
		{
			home = ft_gethome(env);
			ft_setpwd(env, pwd, home);
			return ;
		}
		if (cmd[1])
		{
			if (ft_strcmp(cmd[1], ".") == 0)
			{	
				if((directory = opendir(pwd)) == NULL)
					ft_putendl_fd("OPENDIR ERROR", 1);
				else
					ft_setpwd(env, NULL, NULL);
				return;
			}
			else if (ft_strcmp(cmd[1], "..") == 0)
			{
				tmp = ft_strrchr(pwd, 47);
				i = (ft_strlen(pwd) - ft_strlen(tmp));
				nextpwd = (char *)malloc(sizeof(char) * i);
				while (j < i)
				{
					nextpwd[j] = pwd[j];
					j++;
				}
				nextpwd[j] = '\0';
			}
			else if (strncmp(cmd[1], "../", 3) == 0)
			{
				tmp = ft_strrchr(pwd, 47);
				i = (ft_strlen(pwd) - ft_strlen(tmp));
				ft_putstr("tmp  ->");
				ft_putendl(tmp);
				ft_putnbr(i);
				tmp2 = (char *)malloc(sizeof(char) * i + 1);
				while (j < i)
				{
					tmp2[j] = pwd[j];
					j++;
				}
				tmp2[j] = '\0';
				ft_putstr("tmp2  ->");
				ft_putendl(tmp2);
				tmp = (char*)malloc(sizeof(char)* ft_strlen(cmd[1]) - 1);
				i = 2;
				j = 0;
				while (cmd[1][i] != '\0')
				{
					tmp[j] = cmd[1][i];
					i++;
					j++;
				}
				tmp[i] = '\0';

				nextpwd = ft_strjoin(tmp2, tmp);
				ft_putstr("nextpwd  ->");
				ft_putendl(nextpwd);
				free(tmp); //ok
				free(tmp2);
			}
			else if (ft_strncmp(cmd[1], "/", 1) == 0)
				nextpwd = ft_strdup(cmd[1]);
			else if (ft_strncmp(cmd[1], "~", 1) == 0)
			{
				home = ft_gethome(env);
//				ft_putendl(home);
//				ft_putendl(pwd);
				if (ft_strncmp(cmd[1], "~/", 2) == 0)
				{
					ft_putendl("ok");
					test = ft_strchr(cmd[1], '/');
					ft_putendl(test);
					nextpwd = ft_strjoin(home, test);
					//free(test); //new free
					//free(home);
				}
				else
					nextpwd = home;
			}
			else
			{
				ft_putendl("Normal");
				tmp = ft_strjoin(pwd, "/");
				nextpwd = ft_strjoin(tmp, cmd[1]);
				//free(tmp);
			}
		}
	}

	if(nextpwd && (directory = opendir(nextpwd)) == NULL)
	{
		ft_putendl_fd("OPENDIR ERROR", 1);
		ft_putendl(nextpwd);
		return;
	}
	else
	{
		ft_putendl("Open Success");
		ft_putstr("nextpwd  ---> ");
		ft_putendl(nextpwd);
		ft_putstr("pwd --->");
		ft_putendl(pwd);
		ft_setpwd(env, pwd, nextpwd);
	}
	//free(nextpwd);
	//free(pwd);
}

char		*ft_gethome(t_env	**env){
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ft_strcmp(ptrmaillon->name, "HOME") == 0)
		{
			tmp = ptrmaillon->value;
			return (tmp);
		}
		ptrmaillon = ptrmaillon->next;
	}
	return (NULL);
}

void		ft_setpwd(t_env **env, char *pwd, char *nextpwd){
	t_env	*ptrmaillon;
	char	*tmp;

	ptrmaillon = *env;
	while (ptrmaillon)
	{
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "PWD") == 0)
		{
			if (nextpwd)
			{
				chdir(nextpwd);
				tmp = getcwd(nextpwd, ft_strlen(nextpwd));

				// ft_putstr("nextpwd before parsedot");
				// ft_putendl(nextpwd);
				// tmp = parsedot(nextpwd);
				// ft_putstr("tmp after parsedot");
				// ft_putendl(tmp);
				// tmp = removeslash(tmp);
				ptrmaillon->value = ft_strdup(tmp);
				free(tmp);
				//free(nextpwd);
			}
		}
		if (ptrmaillon->name && ft_strcmp(ptrmaillon->name, "OLDPWD") == 0)
		{
			if (pwd)
			{
				ptrmaillon->value = ft_strdup(pwd);
				//(pwd); // new free
			}
		}
		ptrmaillon = ptrmaillon->next;
	}
}

char	*parsedot(char *str){
	int	start;
	int	end;
	int	i;
	char *str2;
	int action = 0;

	ft_putendl("Parsedot");
	i = 0;
	start = 0;
	end = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
		{
			start = i;
			i++;
			if (str[i] == '.')
			{
				i++;
				if (str[i] == '/')
				{
					end = i - 1;
					action = 1;
					break;
				}
				else if (str[i] == '.')
				{
					i++;
					if (str[i] == '/')
					{
						end = i - 1;
						action = 2;
						break;
					}
				}
			}
		}
		else
			i++;
	}
	if (action == 1)
	{
		ft_putstr("str before new   ->");
		ft_putendl(str);
		str2 = newstr(str, start, end);
		//free(str);
		str2 = parsedot(str2);
		ft_putstr("str2 after parsedot   ->");
		ft_putendl(str2);
		return (str2);
		//parsedot(str2);
		//parsedot(str2);
		//free(str);
	}
	ft_putendl("exit str");
	return (str);
}

char		*removeslash(char *str){
	char	*str2;
	int		i;

	if (str[ft_strlen(str) - 1] == '/')
	{
		ft_putendl("HAVE removeslash");
		i = 0;
		str2 = (char *)malloc(sizeof (char) * ft_strlen(str) - 1);
		while (str[i + 1] != '\0')
		{
			str2[i] = str[i];
			i++;
		}
		str2[i] = '\0';
		//free(str);
		str2 = removeslash(str2);		
		return (str2);
	}
	return (str);
}

char	*newstr(char *str, int start, int end)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newstr = (char *)malloc(sizeof (char) * ft_strlen(str) - 1);
	ft_putnbr(ft_strlen(str) - 1);
	ft_putendl("newstr");
	ft_putnbr(start);
	ft_putendl("");
	ft_putnbr(end);
	ft_putendl("");
	while (str[i] != '\0')
	{
		if (i < start || i > end)
		{
			newstr[j] = str[i];
			j++;
			i++;
		}
		else
		{
			i++;
		}
	}
	newstr[j] = '\0';
	free(str); // OK
	ft_putendl(newstr);
	ft_putnbr(ft_strlen(newstr));
	return (newstr);
}