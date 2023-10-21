/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:53:19 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/21 01:47:10 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*wild_join(char **wild_list);
static char		**wild_sort(t_list *wild_list);
static t_list	*wild_read(char *wildcard, DIR *dir);

char	*wild_get(char *wildcard)
{
	DIR		*dir;
	char	*pwd;
	t_list	*wild_list;
	char	*str;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	dir = opendir(pwd);
	free(pwd);
	if (dir == NULL)
	{
		perror("minishell: ");
		return (NULL);
	}
	wild_list = wild_read(wildcard, dir);
	closedir(dir);
	if (wild_list == NULL)
		return (NULL);
	str = wild_join(wild_sort(wild_list));
	ft_lstclear(&wild_list, free);
	return (str);
}

static t_list	*wild_read(char *wildcard, DIR *dir)
{
	struct dirent	*dirret;
	t_list			*wild_list;

	wild_list = NULL;
	while (true)
	{
		dirret = readdir(dir);
		if (dirret == NULL)
			break ;
		if (ft_strncmp(dirret->d_name, ".", 1) == 0)
			continue ;
		if (wild_match(wildcard, dirret->d_name))
			ft_lstadd_back(&wild_list, ft_lstnew(ft_strdup(dirret->d_name)));
	}
	return (wild_list);
}

static char	**wild_sort(t_list *wild_list)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	**wilds;

	wilds = (char **)ft_lst_to_array(wild_list);
	size = 0;
	while (wilds[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(wilds[i], wilds[j]) > 0)
				ft_pswap((void **)(&wilds[i]), (void **)(&wilds[j]));
			j++;
		}
		i++;
	}
	return (wilds);
}

static char	*wild_join(char **wild_list)
{
	char	*str;
	char	*aux;
	size_t	i;

	i = 0;
	if (wild_list[i] == NULL)
		return (NULL);
	str = ft_strdup("");
	while (wild_list[i] != NULL)
	{
		if (i != 0)
		{
			aux = ft_strjoin(str, " ");
			free(str);
			str = aux;
		}
		aux = ft_strjoin(str, wild_list[i]);
		free(str);
		str = aux;
		i++;
	}
	free(wild_list);
	return (str);
}
