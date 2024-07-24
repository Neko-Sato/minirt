/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:25:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/25 01:42:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "objects/abstract_figure.h"
#include "objects/bvh.h"
#include "objects/bvh_leaf.h"
#include <stdlib.h>

t_rt_errno	bvh_build(t_bvh **bvh, t_abstract_figure **figures, size_t size)
{
	t_rt_errno	ret;
	t_bvh		*tmp;

	if (1 || size < BVH_MAX_FIGURES)
	{
		tmp = malloc(sizeof(t_bvh_leaf));
		if (!tmp)
			return (FAILED_ALLOCATE);
		ret = bvh_leaf_init((void *)tmp, &(t_bvh_leaf_init){figures, size});
		if (ret)
			return (free(tmp), ret);
	}
	else
	{
	}
	*bvh = tmp;
	return (SUCCESS);
}
