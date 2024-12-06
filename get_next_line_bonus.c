/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:08:21 by aedarkao          #+#    #+#             */
/*   Updated: 2024/12/06 15:03:13 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	read_buf(int fd, char **buf, int *read_bytes)
{
	char	*new_cont;
	char	*old_cont;

	old_cont = *buf;
	new_cont = (char *) malloc(BUFFER_SIZE + 1);
	*read_bytes = read(fd, new_cont, BUFFER_SIZE);
	if (*read_bytes > 0)
	{
		new_cont[*read_bytes] = 0;
		*buf = ft_strjoin(old_cont, new_cont);
	}
	free(new_cont);
	free(old_cont);
}

static int	contains_nl(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
			return (1);
	}
	return (0);
}

static int	is_valid(char *buf, int read_bytes)
{
	if (contains_nl(buf) || read_bytes == 0 || read_bytes == -1)
		return (1);
	return (0);
}

static char	*get_ret_buf(char **buf, int read_bytes, char *ret_buf, char *tmp)
{
	int		pos;

	if (!ft_strlen(*buf) || read_bytes == -1)
		return (NULL);
	if (!contains_nl(*buf))
	{
		ret_buf = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
	}
	else
	{
		pos = ft_strchr(*buf, '\n') - *buf;
		ret_buf = ft_substr(*buf, 0, pos + 1);
		tmp = *buf;
		*buf = ft_substr(tmp, pos + 1, ft_strlen(tmp) + 1);
		free(tmp);
		if (!ft_strlen(*buf))
		{
			free(*buf);
			*buf = NULL;
		}
	}
	return (ret_buf);
}

char	*get_next_line(int fd)
{
	static char	*bufs[1024];
	int			read_bytes;
	char		*ret_buf;
	char		*tmp;

	ret_buf = NULL;
	tmp = NULL;
	read_bytes = -2;
	while (1)
	{
		if (is_valid(bufs[fd], read_bytes))
			return (get_ret_buf(bufs + fd, read_bytes, ret_buf, tmp));
		read_buf(fd, bufs + fd, &read_bytes);
	}
}

// int main()
// {
// 	int fd1 = open("greeting.txt", O_RDONLY);
// 	int fd2 = open("name.txt", O_RDONLY);
// 	int fd3 = open("question.txt", O_RDONLY);

// 	char *s;
// 	for (int i = 0; i < 5; i++) {
// 		s = get_next_line(fd1);
// 		printf("%s", s);
// 		free(s);
// 		s = get_next_line(fd2);
// 		printf("%s", s);
// 		free(s);
// 		s = get_next_line(fd3);
// 		printf("%s", s);
// 		free(s);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
