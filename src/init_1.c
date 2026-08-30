/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/08/30 18:27:13 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init_2.c"
#include <stdlib.h>

static int	init_coders(t_sim *sim)
{
	int	i;

	sim->coders = malloc(sizeof(t_coder) * sim->number_of_coders);
	if (!sim->coders)
		return (1);
	i = 0;
	while (i < sim->number_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start = 0;
		sim->coders[i].deadline = 0;
		sim->coders[i].sim = sim;
		i++;
	}
	return (0);
}

static int	init_dongle(t_dongle *dongle, int i)
{
	dongle->id = i;
	dongle->available = 1;
	dongle->cooldown_until = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (1);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	return (0);
}

static void	destroy_dongles(t_sim *sim, int i)
{
	while (i > 0)
	{
		i--;
		pthread_cond_destroy(&sim->dongles[i].cond);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
	}
	free(sim->dongles);
	sim->dongles = NULL;
}

static int	init_dongles(t_sim *sim)
{
	int	i;

	sim->dongles = malloc(sizeof(t_dongle) * sim->number_of_coders);
	if (!sim->dongles)
		return (1);
	i = 0;
	while (i < sim->number_of_coders)
	{
		if (init_dongle(&sim->dongles[i], i + 1))
		{
			destroy_dongles(sim, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_sim(t_sim *sim)
{
	sim->stop = 0;
	if (init_coders(sim))
		return (1);
	if (init_dongles(sim))
	{
		free(sim->coders);
		sim->coders = NULL;
		return (1);
	}
	init_coder_dongles(sim);
	return (0);
}
