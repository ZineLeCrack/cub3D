/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:57:45 by rlebaill          #+#    #+#             */
/*   Updated: 2025/02/08 14:28:21 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buff)
{
	char	*tmp;
	char	*line;
	char	*new_line;
	ssize_t	bytes_read;

	line = ft_strjoin_gnl(buff, "");
	while (!ft_strchr_gnl(line, '\n'))
	{
		tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tmp)
			return (free(line), NULL);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), free(tmp), NULL);
		if (bytes_read == 0)
			return (free(tmp), line);
		tmp[bytes_read] = '\0';
		new_line = ft_strjoin_gnl(line, tmp);
		free(line);
		free(tmp);
		line = ft_strdup_gnl(new_line);
		free(new_line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buff);
	if (!line)
		return (buff[0] = '\0', NULL);
	if (!line[0])
		return (free(line), NULL);
	if (!ft_strchr_gnl(line, '\n'))
		return (ft_strcpy_gnl(buff, ""), line);
	ft_strcpy_gnl(buff, ft_strchr_gnl(line, '\n') + 1);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n' && line[i + 1])
		line[i + 1] = '\0';
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char *line;

// 	fd = open("get_next_line_utils.c", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
