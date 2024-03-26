/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:44:44 by mateo             #+#    #+#             */
/*   Updated: 2024/03/26 11:20:10 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_gnl_lstclear(t_gnl_list **lst, int forward, t_gnl *meta)
{
	t_gnl_list	*start;
	t_gnl_list	*next;

	if (!lst || !(*lst))
		return (0);
	if (meta)
		free(meta);
	start = *lst;
	next = 0;
	while (start)
	{
		if (forward == 1)
			next = start->next;
		else
			next = start->prev;
		free(start->str);
		start->str = 0;
		free(start);
		start = next;
	}
	(*lst) = 0;
	return (0);
}

t_gnl_list	*ft_lstaddnew(t_gnl_list **head, int csize)
{
	t_gnl_list	*new;
	t_gnl_list	*last;

	new = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!new)
		return (0);
	new->next = 0;
	new->prev = 0;
	new->nl = 0;
	new->eof = 0;
	if (!(*head))
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
	new->str = malloc(csize * sizeof(char));
	if (!(new->str))
		return (0);
	return (new);
}

t_gnl_list	*ft_lstsplit(t_gnl_list *last, char *newline)
{
	t_gnl_list	*new;
	int			newlen;
	int			i;

	last->nl = 1;
	newlen = ft_strchr(last->str, '\0') - newline - 1;
	newline++;
	if (*newline != '\0')
	{
		new = ft_lstaddnew(&last, newlen + 1);
		if (!new)
			return (0);
		new->str[newlen] = '\0';
		i = -1;
		while (i++ < newlen)
			new->str[i] = *(newline + i);
		if (last->eof == 1)
		{
			last->eof = 0;
			new->eof = 1;
		}
		*newline = '\0';
		return (new);
	}
	return (last);
}

int	ft_lststrlen(t_gnl_list *head, t_gnl_list *last)
{
	int		totlen;
	char	*temp;

	totlen = 0;
	if (head == last)
	{
		temp = head->str;
		while (*temp++)
			totlen++;
	}
	else
	{
		while (head->nl == 0 && head->eof == 0)
		{
			temp = head->str;
			while (*temp++)
				totlen++;
			head = head->next;
		}
		temp = head->str;
		while (*temp++)
			totlen++;
	}
	return (totlen);
}
