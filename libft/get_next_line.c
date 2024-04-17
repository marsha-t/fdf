/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 07:07:10 by mateo             #+#    #+#             */
/*   Updated: 2024/04/17 17:46:28 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lststrcat(int len, t_gnl_list **head, char *fullline, t_gnl *meta)
{
	int		i;
	int		j;

	i = 0;
	while (i < len && ((*head)->next))
	{
		j = 0;
		while ((*head)->str[j])
			fullline[i++] = (*head)->str[j++];
		*head = (*head)->next;
	}
	if (i == len)
		ft_gnl_lstclear(&(*head)->prev, 0, meta);
	else
	{
		j = 0;
		while ((*head)->str[j])
			fullline[i++] = (*head)->str[j++];
		ft_gnl_lstclear(head, 0, meta);
	}
	return (fullline);
}

char	*ft_lststrcat_setup(t_gnl_list **head, t_gnl_list *last, t_gnl *meta)
{
	char	*fullline;
	int		len;

	len = ft_lststrlen(*head, last);
	if (!len)
		return (ft_gnl_lstclear(head, 1, meta));
	fullline = malloc((len + 1) * sizeof(char));
	if (!fullline)
		return (ft_gnl_lstclear(head, 1, meta));
	fullline[len] = '\0';
	fullline = ft_lststrcat(len, head, fullline, meta);
	return (fullline);
}

t_gnl	*ft_gnl_meta(int fd, int free_static, t_gnl_list **head)
{
	t_gnl	*meta;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	meta = malloc(sizeof(t_gnl));
	if (!meta)
		return (0);
	meta->fd = fd;
	meta->read_r = 1;
	meta->newline = 0;
	if (free_static == 1)
		return (ft_gnl_lstclear(head, 1, meta));
	if (meta->read_r >= 0 && *head)
		meta->newline = ft_strchr((*head)->str, '\n');
	if (read(fd, 0, 0) < 0)
		return (ft_gnl_lstclear(head, 1, meta));
	return (meta);
}

char	*get_next_line(int fd, int free_static)
{
	static t_gnl_list	*head;
	t_gnl_list			*last;
	t_gnl				*meta;

	meta = ft_gnl_meta(fd, free_static, &head);
	if (!meta)
		return (0);
	last = head;
	while (meta->read_r > 0 && !(meta->newline))
	{
		last = ft_lstaddnew(&head, BUFFER_SIZE + 1);
		if (!last)
			return (ft_gnl_lstclear(&head, 1, meta));
		meta->read_r = read(fd, last->str, BUFFER_SIZE);
		last->str[meta->read_r] = '\0';
		meta->newline = ft_strchr(last->str, '\n');
	}
	if (meta->read_r == 0)
		last->eof = 1;
	if (meta->read_r >= 0 && meta->newline)
		last = ft_lstsplit(last, meta->newline);
	if (meta->read_r >= 0 && last)
		return (ft_lststrcat_setup(&head, last, meta));
	return (ft_gnl_lstclear(&head, 1, meta));
}
