/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:19:40 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/light.h"
#include "parser.h"
#include "rt_errno.h"
#include <stdlib.h>

static inline int	parse_light2(char **str, t_scene *scene, char *s,
						t_light *tmp);

int	parse_light(char **str, t_scene *scene)
{
	int		ret;
	char	*s;
	t_light	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (FAILED_ALLOCATE);
	ret = light_init(tmp);
	if (ret)
		return (free(tmp), ret);
	s = *str;
	ret = parse_vec3d(&s, &tmp->coordinates);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	ret = parse_rate(&s, &tmp->brightness);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	ret = parse_blank(&s);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	return (parse_light2(str, scene, s, tmp));
}

static inline int	parse_light2(char **str, t_scene *scene, char *s,
		t_light *tmp)
{
	int	ret;

	ret = parse_color(&s, &tmp->color);
	if (ret)
		return (light_del(tmp), free(tmp), ret);
	ret = scene_add_light(scene, tmp);
	if (ret)
		return (light_del(tmp), free(tmp), FAILED_ALLOCATE);
	*str = s;
	return (SUCCESS);
}
