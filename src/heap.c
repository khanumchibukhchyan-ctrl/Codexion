/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchibukh <kchibukh@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 14:33:22 by kchibukh          #+#    #+#             */
/*   Updated: 2026/09/04 18:01:00 by kchibukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_heap(t_sim *sim)
{
}

void	sift_up(t_heap *heap, int index)
{
	t_request	temp;
	int			parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (heap->items[parent].deadline <= heap->items[index].deadline)
			break ;
		temp = heap->items[parent];
		heap->items[parent] = heap->items[index];
		heap->items[index] = temp;
		index = parent;
	}
}

void	sift_down(t_heap *heap, int index)
{
	t_request	temp;
	int			parent;
	int			left;
	int			right;
	int			smallest;

	while (1)
	{
		left = 2 * index + 1;
		right = 2 * index + 2;
		smallest = index;
		if (left < heap->size
			&& heap->items[left].deadline < heap->items[smallest].deadline)
			smallest = left;
		if (right < heap->size
			&& heap->items[right].deadline < heap->items[smallest].deadline)
			smallest = right;
		if (smallest == index)
			break ;
		temp = heap->items[index];
		heap->items[index] = heap->items[smallest];
		heap->items[smallest] = temp;
		index = smallest;
	}
}
