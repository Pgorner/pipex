/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:25:16 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/19 21:13:27 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "pipex.h"

void	input(int argc, char *argv[], t_s *vs)
{
	char	*i;
	int		fd;
	char	*line;
	char	*val;

	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	free (line);
	val = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	i = line;
	while (i)
	{
		val = ft_strjoin(val, line);
		free(line);
		line = get_next_line(fd);
		i = line;
	}
	vs->input = val;
	vs->output = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free (val);
	close (fd);
}
 */
