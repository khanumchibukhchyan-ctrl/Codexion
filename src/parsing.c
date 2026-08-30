/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/08/30 14:55:06 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "codexion.h"
#include <string.h>

long	ft_atol(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	check(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '\0')
		return (1);
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (check(argv[i]))
			return (1);
		i++;
	}
	if (strcmp(argv[8], "FIFO") != 0 && strcmp(argv[8], "EDF") != 0)
		return (1);
	return (0);
}

int	parse(int argc, char **argv, t_sim *sim)
{
	if (argc != 9)
	{
		printf("Invalid number of arguments.\n");
		return (1);
	}
	if (check_args(argv))
	{
		printf("Invalid argument.\n");
		return (1);
	}
	sim->number_of_coders = atoi(argv[1]);
	sim->time_to_burnout = ft_atol(argv[2]);
	sim->time_to_compile = ft_atol(argv[3]);
	sim->time_to_debug = ft_atol(argv[4]);
	sim->time_to_refactor = ft_atol(argv[5]);
	sim->number_of_compiles_required = atoi(argv[6]);
	sim->dongle_cooldown = ft_atol(argv[7]);
	sim->scheduler = argv[8];
	return (0);
}
