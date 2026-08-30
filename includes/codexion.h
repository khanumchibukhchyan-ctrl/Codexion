/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/08/30 18:49:38 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_sim		t_sim;
typedef struct s_request	t_request;
typedef struct s_heap		t_heap;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_start;
	long			deadline;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	t_sim			*sim;
}	t_coder;

typedef struct s_dongle
{
	int				id;
	int				available;
	long			cooldown_until;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_sim
{
	int				stop;
	int				number_of_coders;
	int				number_of_compiles_required;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			dongle_cooldown;
	char			*scheduler;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor;
	pthread_mutex C4      C2_t	print_mutex;
	pthread_mutex_t	state_mutex;
	t_heap			*request_heap;
}	t_sim;

typedef struct s_request
{
	t_coder		*coder;
	long		timestamp;
	long		deadline;
}	t_request;

typedef struct s_heap
{
	t_request	*items;
	int			size;
	int			capacity;
}	t_heap;

int		parse(int argc, char **argv, t_sim *sim);
int		check(char *argv);
int		check_args(char **argv);
long	ft_atol(char *str);

#endif