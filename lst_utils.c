/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 00:39:24 by madaguen          #+#    #+#             */
/*   Updated: 2024/01/21 19:11:58 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	add_to_list(char *line, t_lst **lst)
{
	t_lst	*new;
	t_lst	*tmp;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (write(2, "MALLOC FAILURE\n", 16), 0);
	new->next = NULL;
	new->data = line;
	tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void	del_one(t_lst **lst, t_lst *node)
{
	t_lst	*tmp;

	tmp = *lst;
	if (tmp == node)
		*lst = (*lst)->next;
	else
	{
		while (tmp->next != node)
			tmp = tmp->next;
		tmp->next = node->next;
	}
	free(tmp->data);
	free(node);
}

void	lst_clear(t_lst **lst)
{
	t_lst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		free((*lst)->data);
		free(*lst);
	}
}

int	lst_size(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**lst_to_tab(t_lst *lst)
{
	int		i;
	char	**dest;
	t_lst	*tmp;

	i = 0;
	dest = malloc(sizeof(char *) * (lst_size(lst) + 1));
	if (!dest)
		return (write(2, "MALLOC FAILURE\n", 16), NULL);
	while (lst)
	{
		tmp = lst;
		dest[i] = lst->data;
		i++;
		lst = lst->next;
		free(tmp);
	}
	dest[i] = NULL;
	return (dest);
}
