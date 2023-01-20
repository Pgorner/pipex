/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:44:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/20 16:31:15 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_s *vs)
{
	dup2(vs->input, STDIN);
	dup2(vs->pfeife[WRITE], STDOUT);
	close(vs->pfeife[READ]);
	close(vs->input);
	execve(vs->pone, vs->one, vs->env);
}

void	parent(t_s *vs)
{
	dup2(vs->output, STDOUT);
	dup2(vs->pfeife[READ], STDIN);
	close(vs->pfeife[WRITE]);
	close(vs->output);
	execve(vs->ptwo, vs->two, vs->env);
}
