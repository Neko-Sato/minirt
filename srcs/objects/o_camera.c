/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:02:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 08:40:29 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_fov(char *str, int *value);

int	o_camera_parser(char *str, t_object *object)
{
	static const size_t			size = 3;
	static const t_parser_entry	entries[] = {
	{offsetof(t_o_camera, coordinates), (t_parser_fun)parse_vec3d},
	{offsetof(t_o_camera, orientation), (t_parser_fun)parse_norm_vec3d},
	{offsetof(t_o_camera, fov), (t_parser_fun)parse_fov},
	};
	t_o_camera *const			camera = &object->value.camera;

	object->type = o_camera;
	return (parser(str, entries, size, camera));
}

static int	parse_fov(char *str, int *value)
{
	int	ret;
	int	tmp;

	ret = parse_int(str, &tmp);
	if (ret)
		return (ret);
	if (tmp < 0 || 180 < tmp)
		return (INCORRECT_FORMAT);
	*value = tmp;
	return (NO_ERROR);
}
