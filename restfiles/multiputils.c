/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:44:45 by pgorner           #+#    #+#             */
/*   Updated: 2023/01/20 15:06:01 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_s *vs)
{
	dup2(vs->input, 0);
	dup2(vs->pfeife[1], 1);
	close(vs->pfeife[0]);
	close(vs->input);
	execve(vs->pone, vs->one, vs->env);
}

void	parent(t_s *vs)
{
	dup2(vs->output, 0);
	dup2(vs->pfeife[0], 0);
	close(vs->pfeife[1]);
	close(vs->output);
	execve(vs->ptwo, vs->two, vs->env);
}
