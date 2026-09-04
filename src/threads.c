/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/09/03 17:50:08 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// static void *coder_routine(void *arg)
// {
// 	t_coder	*coder;

// 	coder = (t_coder *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&coder->mutex);
// 		if (coder->task != NULL)
// 		{
// 			coder->task->execute(coder->task);
// 			coder->task = NULL;
// 		}
// 		pthread_mutex_unlock(&coder->mutex);
// 	}
// 	return (NULL);
// }

static void	create_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
		{
			destroy_threads(sim, i);
			return ;
		}
		i++;
	}
}
