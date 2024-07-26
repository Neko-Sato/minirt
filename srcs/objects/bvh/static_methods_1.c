/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:25:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/26 09:25:06 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_inner.h"
#include "objects/bvh_leaf.h"
#include <libft.h>
#include <stdlib.h>

static inline t_bvh	*new_bvh_leaf(t_abstract_figure **figures, size_t size)
{
	t_bvh_leaf	*bvh;

	bvh = malloc(sizeof(*bvh));
	if (!bvh)
		return (NULL);
	bvh_leaf_init(bvh, &(t_bvh_leaf_init){figures, size});
	return ((void *)bvh);
}

static inline t_bvh	*new_bvh_inner(t_bvh *left, t_bvh *right)
{
	t_bvh_inner	*bvh;

	bvh = malloc(sizeof(*bvh));
	if (!bvh)
		return (NULL);
	bvh_inner_init(bvh, &(t_bvh_inner_init){left, right});
	return ((void *)bvh);
}

static inline int	push_task(t_bvh_build_local *_)
{
	if (!_->task.left)
	{
		_->task.split = bvh_figures_split(&_->figures[_->task.start],
				_->task.size);
		if (ft_stack_push(&_->stack, &_->task, sizeof(_->task)))
			return (-1);
		_->task = (t_bvh_task){NULL, NULL, _->task.start, _->task.split, 0};
	}
	else
	{
		if (ft_stack_push(&_->stack, &_->task, sizeof(_->task)))
			return (-1);
		_->task = (t_bvh_task){NULL, NULL, _->task.start + _->task.split,
			_->task.size - _->task.split, 0};
	}
	return (0);
}

static inline int	bvh_build_internal(t_bvh_build_local *_)
{
	while (1)
	{
		if (_->task.size < BVH_MAX_FIGURES)
		{
			_->tmp = new_bvh_leaf(&_->figures[_->task.start], _->task.size);
			while (1)
			{
				if (!_->tmp)
					return (-1);
				if (ft_stack_pop(&_->stack, &_->task))
					return (0);
				if (!_->task.left)
					break ;
				_->task.right = _->tmp;
				_->tmp = new_bvh_inner(_->task.left, _->task.right);
			}
			_->task.left = _->tmp;
		}
		if (push_task(_))
			return (-1);
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
