/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:25:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/26 04:17:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_inner.h"
#include "objects/bvh_leaf.h"
#include <libft.h>
#include <stdlib.h>

void	bvh_sort(t_abstract_figure **figures, size_t size, int axis)
{
	size_t				i;
	size_t				j;
	t_abstract_figure	*tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (figures[i]->aabb.min._[axis] > figures[j]->aabb.min._[axis])
			{
				tmp = figures[i];
				figures[i] = figures[j];
				figures[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

float	bvh_cost(t_abstract_figure **figures, size_t size)
{
	t_aabb	aabb;
	size_t	i;

	i = 0;
	aabb = figures[i++]->aabb;
	while (i < size)
		aabb = aabb_merge(&aabb, &figures[i++]->aabb);
	return (aabb_surface_area(&aabb));
}

void	bvh_best_split(t_abstract_figure **figures, size_t size, int *best_axis,
		float *best_point)
{
	int		axis;
	float	cost;
	float	best_cost;

	best_cost = INFINITY;
	axis = 0;
	while (axis < 3)
	{
		bvh_sort(figures, size, axis);
		cost = bvh_cost(figures, size / 2);
		cost += bvh_cost(figures + (size / 2), size - (size / 2));
		if (axis == 0 || cost < best_cost)
		{
			*best_axis = axis;
			*best_point = figures[size / 2]->aabb.min._[axis];
			best_cost = cost;
		}
		axis++;
	}
}

size_t	bvh_split(t_abstract_figure **figures, size_t size)
{
	int		axis;
	float	point;
	size_t	i;

	axis = 0;
	point = 0;
	bvh_best_split(figures, size, &axis, &point);
	bvh_sort(figures, size, axis);
	i = 0;
	while (i < size && figures[i]->aabb.min._[axis] < point)
		i++;
	return (i);
}

typedef struct s_bvh_task
{
	t_bvh				*left;
	t_bvh				*right;
	size_t				start;
	size_t				size;
	size_t				split;
}						t_bvh_task;

typedef struct s_bvh_build_local
{
	t_abstract_figure	**figures;
	size_t				size;
	t_stack				*stack;
	t_bvh_task			task;
	t_bvh				*tmp;
}						t_bvh_build_local;

static inline int	bvh_build_internal(t_bvh_build_local *_)
{
	while (1)
	{
		if (_->task.size < BVH_MAX_FIGURES)
		{
			_->tmp = malloc(sizeof(t_bvh_leaf));
			if (!_->tmp)
				return (-1);
			bvh_leaf_init((void *)_->tmp,
				&(t_bvh_leaf_init){&_->figures[_->task.start], _->task.size});
			if (ft_stack_pop(&_->stack, &_->task))
				return (0);
			while (_->task.left)
			{
				_->task.right = _->tmp;
				_->tmp = malloc(sizeof(t_bvh_inner));
				if (!_->tmp)
					return (-1);
				bvh_inner_init((void *)_->tmp, &(t_bvh_inner_init){_->task.left,
					_->task.right});
				if (ft_stack_pop(&_->stack, &_->task))
					return (0);
			}
			_->task.left = _->tmp;
			if (ft_stack_push(&_->stack, &_->task, sizeof(_->task)))
				return (-1);
			_->task = (t_bvh_task){NULL, NULL, _->task.start + _->task.split,
				_->task.size - _->task.split, 0};
		}
		else
		{
			_->task.split = bvh_split(&_->figures[_->task.start], _->task.size);
			if (ft_stack_push(&_->stack, &_->task, sizeof(_->task)))
				return (-1);
			_->task = (t_bvh_task){NULL, NULL, _->task.start, _->task.split, 0};
		}
	}
}

t_rt_errno	bvh_build(t_bvh **bvh, t_abstract_figure **figures, size_t size)
{
	t_bvh_build_local	_;

	_.figures = figures;
	_.size = size;
	_.stack = NULL;
	_.task = (t_bvh_task){NULL, NULL, 0, size, 0};
	if (bvh_build_internal(&_))
	{
		while (1)
		{
			_.task.left->_->del(_.task.left);
			free(_.task.left);
			_.task.right->_->del(_.task.right);
			free(_.task.right);
			if (ft_stack_pop(&_.stack, &_.task))
				break ;
		}
		return (FAILED_ALLOCATE);
	}
	*bvh = _.tmp;
	return (SUCCESS);
}
