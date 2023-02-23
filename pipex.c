/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:15:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/23 15:46:43 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char *c, int exc)
{
	ft_printf(c);
	exit(exc);
}

char	*check_path(t_s *vs, char *cpath)
{
	int		i;
	int		j;
	int		c;
	char	*tmp;

	c = 0;
	while (vs->env[c])
	{
		i = 0;
		j = 0;
		tmp = ft_calloc(1, ft_strlen(cpath) + ft_strlen(vs->env[c]) + 1);
		while (vs->env[c][i] != '\0')
		{
			tmp[i] = vs->env[c][i];
			i++;
		}
		while (cpath[j] != '\0')
			tmp[i++] = cpath[j++];
		tmp[i] = '\0';
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		c++;
	}
	return (NULL);
}

void	free_leaks(t_s *vs)
{
	int	i;

	i = 0;
	while (vs->one[i])
		free(vs->one[i++]);
	free(vs->one);
	i = 0;
	while (vs->two[i])
		free(vs->two[i++]);
	free(vs->two);
	i = 0;
	while (vs->env[i])
		free(vs->env[i++]);
	free(vs->env);
	free(vs->one);
	free(vs->two);
	free(vs);
}

void	set_vs(int argc, char *argv[], char *env[], t_s *vs)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			vs->env = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (vs->env[i])
	{
		vs->env[i] = ft_strjoin(vs->env[i], "/");
		i++;
	}
	vs->env2 = env;
	vs->one = ft_split(argv[2], ' ');
	vs->two = ft_split(argv[3], ' ');
	vs->input = open(argv[1], O_RDONLY);
	vs->output = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (vs->output < 0 || vs->input < 0)
		ft_exit("Failed to open input/output file", 1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_s	vs;
	int	gabel;

	if (argc != 5)
		ft_exit("Invalid input", 0);
	set_vs(argc, argv, env, &vs);
	vs.pone = check_path(&vs, vs.one[0]);
	vs.ptwo = check_path(&vs, vs.two[0]);
	if (pipe(vs.pfeife) < 0)
		exit(0);
	gabel = fork();
	if (gabel == 0)
		child(&vs);
	else
		parent(&vs);
	if (access(vs.pone, F_OK) == 0)
		parent(&vs);
	free_leaks(&vs);
	exit(0);
	return (0);
}
