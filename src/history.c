#include "minishell.h"

void			add_to_history(char *cmd, t_hist **history)
{
	t_hist		*ptrh;
	t_hist		*newh;


	newh = inithist();
	if (!*history)
	{
		*history = newh;
		newh->cmd = ft_strdup(cmd);
		newh->next = NULL;
		return ;
	}
	ptrh = *history;
	while (ptrh->next)
		ptrh = ptrh->next;
	ptrh->next = newh;
	newh->cmd = ft_strdup(cmd);
	newh->next = NULL;
}

void			show_history(t_hist **history)
{
	t_hist		*ptrh;

	ptrh = *history;
	ft_putstr("\t\t ...history...\n");
	while (ptrh)
	{
		ft_putendl(ptrh->cmd);
		ptrh = ptrh->next;
	}
}

t_hist 			*inithist(void)
{
	t_hist		*newh;

	newh = (t_hist *)malloc(sizeof(t_hist));
	newh->cmd = NULL;
	newh->next = NULL;
	return (newh);
}