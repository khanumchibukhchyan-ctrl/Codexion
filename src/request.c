/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/09/04 17:58:25 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_request(t_request *request, t_coder *coder)
{
	request->coder = coder;
	request->timestamp = get_time(coder->sim);
	request->deadline = coder->deadline;
}

int	push_request(t_request *request, t_heap *heap)
{
	if (heap->size >= heap->capacity)
		return (1);
	heap->items[heap->size] = *request;
	heap->size++;
	if (strcmp(heap->sim->scheduler, "edf") == 0)
		sift_up(heap, heap->size - 1);
	return (0);
}
