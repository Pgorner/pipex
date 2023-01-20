/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:15:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/20 16:28:13 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

/* int	getpath(char *env[])
{

} */

void	ft_exit(char *c, int exc)
{
	ft_printf(c);
	exit(exc);
}

/* void	check(int argc, char *argv[], char *env[], t_s *vs)
{
	if (!env)
		ft_exit("Invalid environment variable", 1);
	if (argc != 5)
		ft_exit("Invalid input", 2);
	if (access(argv[1], R_OK) < 0 || access(argv[4], W_OK) < 0)
		ft_exit("Missing access priviliges", 3);
	if (pipe(vs->pfeife)  < 0)
		ft_exit("Where da pipe at?\n", 4);
}
 */

char	*check_path(t_s *vs, char *cpath)
{
	int i;
	int j;
	int c;
	char *tmp;

	c = 0;
	while (vs->env[c])
	{
		i = 0;
		j = 0;
		tmp = ft_calloc(sizeof(char), ft_strlen(cpath) + ft_strlen(vs->env[c]) + 1);
		while (vs->env[c][i] != '\0')
		{
			tmp[i] = vs->env[c][i];
			i++;
		}
		tmp[i++] = '/';
		while (cpath[j] != '\0')
			tmp[i++] = cpath[j++];
		tmp[i] = '\0';
		if (access(tmp, F_OK) == 0)
		{
			return(tmp);
		}
		free(tmp);
		c++;
	}
	if (access(cpath, F_OK) != 0)
	{
		ft_printf("Command not found: \"%s\" \n", cpath);
		//free_leaks(vs);
	}
	return (NULL);
}
/* void	free_leaks(t_s *vs)
{

} */

void	set_vs(int argc, char *argv[], char *env[], t_s *vs)
{
	while (!ft_strnstr(*env, "PATH", 4))
		env++;
	vs->env = (ft_split(*env + 5 , ':'));
	vs->one = ft_split(argv[2], ' ');
	vs->two = ft_split(argv[3], ' ');
	vs->input = open(argv[1], O_RDONLY);
	vs->output = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int		main(int argc, char *argv[], char *env[])
{
	t_s vs;
	int	gabel;

	set_vs(argc, argv, env, &vs);
	pipe(vs.pfeife);
	//check(argc, argv, env, &vs);
	vs.pone = check_path(&vs, vs.one[0]);
	vs.ptwo = check_path(&vs, vs.two[0]);
	gabel = fork();
	if (gabel < 0)
		ft_exit("No forks given", 5);
	if (gabel == 0)
		child(&vs);
	else
		parent(&vs);
	close (vs.pfeife[0]);
	close (vs.pfeife[1]);
	/* 	free_leaks(&vs); */
	return (0);
}

/* 	system("leaks pipex"); */
