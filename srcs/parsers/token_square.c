/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:30:09 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/22 01:37:43 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/square.h"
#include "parser.h"
#include "rt_errno.h"
#include <math.h>
#include <stdlib.h>

static inline int	parse_square2(char **str, t_scene *scene, char *s,
						t_square *tmp);

int	parse_square(char **str, t_scene *scene)
{
	int			ret;
	char		*s;
	t_square	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = square_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_norm_vec3d(&s, &tmp->orientation);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	if (!vec3d_abs(tmp->orientation))
		return (square_del(tmp), free(tmp), AMBIGUOUS_ORIENTATION);
	return (parse_square2(str, scene, s, tmp));
}

static inline int	parse_square2(char **str, t_scene *scene, char *s,
		t_square *tmp)
{
	int	ret;

	ret = parse_blank(&s);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_decimal(&s, &tmp->size, 1);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_color(&s, &((t_figure *)tmp)->color);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = parse_optional(&s, (t_parse_optional_fn)parse_figure_optional, tmp);
	if (ret)
		return (square_del(tmp), free(tmp), ret);
	ret = scene_add_figure(scene, (t_figure *)tmp);
	if (ret)
		return (square_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
