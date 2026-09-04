/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/09/04 16:35:58 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_coder_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		sim->coders[i].left = &sim->dongles[i];
		sim->coders[i].right = &sim->dongles[(i + 1)
			% sim->number_of_coders];
		i++;
	}
}

static int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&sim->state_mutex, NULL))
	{
		pthread_mutex_destroy(&sim->print_mutex);
		return (1);
	}
	return (0);
}
