/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthierr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:32:59 by juthierr          #+#    #+#             */
/*   Updated: 2017/03/22 19:27:04 by juthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

int				ft_fill_line(t_line *start, int fd, char **line, int l)
{
	t_line	*tmp;
	char	*occ;
	int		i;
	char	*frit;

	tmp = start;
	while (tmp->next != NULL && tmp->fd != fd)
		tmp = tmp->next;
	occ = ft_strchr(tmp->mem, '\n');
	if (occ == NULL && l == 0)
	{
		*line = ft_strdup(tmp->mem);
		return (0);
	}
	else if (occ == NULL && l != 0)
		return (2);
	i = occ - tmp->mem;
	if (!(*line = ft_strnew(i)))
		return (-1);
	ft_strncpy(*line, tmp->mem, i);
	frit = ft_strdup(occ + 1);
	free(tmp->mem);
	tmp->mem = frit;
	return (1);
}

int				ft_add_elem(t_line **start, char *buf, int fd)
{
	t_line	*new;

	new = *start;
	while (new)
	{
		if (new->fd == fd)
			return (1);
		new = new->next;
	}
	if (!(new = (t_line*)malloc(sizeof(t_line))))
		return (-1);
	new->mem = ft_strdup(buf);
	new->fd = fd;
	if (!(*start))
	{
		*start = new;
		(*start)->next = NULL;
	}
	else
		(*start)->next = new;
	return (1);
}

int				ft_start_list(t_line *start, char *buf, int fd)
{
	t_line	*tmp;
	char	*stock;
	int		len;

	tmp = start;
	while (tmp->next != NULL && tmp->fd != fd)
	{
		tmp = tmp->next;
	}
	if (tmp->fd == fd)
	{
		len = (int)ft_strlen(tmp->mem);
		if (!(tmp->mem = ft_realloc(tmp->mem, (int)ft_strlen(tmp->mem),
						((int)ft_strlen(tmp->mem) + BUFF_SIZE + 1))))
			return (-1);
		if (*buf != '\0')
			ft_strcat(tmp->mem, buf);
	}
	else
	{
		if (ft_add_elem(&tmp, buf, fd) == -1)
			return (-1);
	}
	ft_bzero(buf, BUFF_SIZE);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*start;
	char			*buf;
	int				l;
	int				test;

	if (!(buf = ft_strnew(BUFF_SIZE + 1)) || (fd < 0))
		return (-1);
	while ((l = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		if (l == -1)
			return (-1);
		if (!(ft_add_elem(&start, buf, fd)))
			return (-1);
		if ((!(ft_start_list(start, buf, fd)) && *buf != '\0'))
			return (-1);
		if ((test = ft_fill_line(start, fd, line, l)) != 2)
		{
			free(buf);
			return (test);
		}
		if (l == 0)
			return (1);
	}
	return (-1);
}
