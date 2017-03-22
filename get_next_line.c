/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juthierr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:32:59 by juthierr          #+#    #+#             */
/*   Updated: 2017/02/27 06:19:55 by juthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

static int				ft_memline(t_line *start, char *buf, char **line, int fd)
{
	t_line	*tmp;
	t_line	*new;
	int i;
	char *occ;

	tmp = start;
	while (tmp->next != NULL && tmp->fd != fd)
		tmp = tmp->next;
		printf("%s \n", "dddddddd");
	if (tmp->fd == fd && ft_strcmp(tmp->mem, buf) != 0)
	{	
		tmp->mem = ft_realloc(tmp->mem, (int)ft_strlen(tmp->mem),
				ft_strlen(tmp->mem) + BUFF_SIZE);
		ft_strcat(tmp->mem, buf);
		printf("%s \n", "eeeeeeee");
		if ((occ = ft_strchr(tmp->mem, '\n')) >= 0)
		{
			*occ = '\0';
			i = occ - tmp->mem;
			if (!(*line = (char *)malloc(i)))
				return (-1);
		printf("%s \n", "ffffffff");
			ft_strncpy(*line, tmp->mem, i);
			free(tmp->mem);

			tmp->mem = occ + 1;
			return (1);
		}
		return (0);
	}
	else
	{
		if (!(new = (t_line*)malloc(sizeof(t_line))))
			return (-1);
		new->mem = ft_strdup(buf);
		new->fd = fd;
		tmp->next = new;	
	}
	return (2);
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*start;
	char 			*buf;
	int 			l;
	int				verif;

	if (fd < 0 || fd > 5000)
		return (-1);
	if (!(buf = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	while ((l = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		printf("%i\n", l);
		if (l == -1)
			return (-1);
		if (!(start))
		{
			printf("wefwefwefew\n");
			if (!(start = (t_line *)malloc(sizeof(t_line))))
				return (-1);
			start->mem = ft_strdup(buf);
			start->fd = fd;
			exit(0);
		}
		printf("%s \n", "bbbbbbbb");
		if ((verif = ft_memline(start, buf, line, fd)) == 2)
		{
		printf("%s \n", "ccccccccc");
			ft_memline(start, buf, line, fd);
		}
		if (verif == -1)
			return (-1);
		if (verif == 1)
			return (1);
	}
	return (0);
}

int 			main(int ac, char **argv)
{
	int fd;
	char *test;
	char *test2;

	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &test);
	ft_putstr(test);
	printf("%s \n", "aaaaaaa");
	fd = open(argv[2], O_RDONLY);
	get_next_line(fd, &test2);
	ft_putstr(test2);
	ft_putchar('\n');
	return (0);
}