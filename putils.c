/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:44:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/02/23 13:19:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_s *vs)
{
	if (vs->pone != NULL)
	{
		dup2(vs->input, STDIN);
		close(vs->input);
		dup2(vs->pfeife[WRITE], STDOUT);
		close(vs->pfeife[READ]);
		if (access(vs->pone, F_OK) == 0)
			if (execve(vs->pone, vs->one, vs->env2) < 0)
				exit(0);
	}
}

void	parent(t_s *vs)
{
	if (vs->ptwo != NULL)
	{
		dup2(vs->output, STDOUT);
		close(vs->output);
		dup2(vs->pfeife[READ], STDIN);
		close(vs->pfeife[WRITE]);
		if (access(vs->ptwo, F_OK) == 0)
			if (execve(vs->ptwo, vs->two, vs->env2) < 0)
				exit(0);
	}
}
