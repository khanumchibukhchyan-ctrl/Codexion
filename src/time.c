/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/09/03 18:20:01 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>

long	get_time(t_sim *sim)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000L + tv.tv_usec / 1000L)
		- sim->simulation_start);
}

void	print_status(t_coder *coder, char *message)
{
	long	time;

	time = get_time(coder->sim);
	if (time < 0)
		return ;
	pthread_mutex_lock(&coder->sim->print_mutex);
	printf("%ld %d %s\n", time, coder->id, message);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
