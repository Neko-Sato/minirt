/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:45:16 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 16:16:35 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"
#include "rt_error.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>

static int			load_rt_internal(t_minirt *rt, t_bufferio *f);
static int			set_rt(t_minirt *rt, t_object *object);
static inline int			set_rt2(t_minirt *rt, t_object *object);

int	load_rt(t_minirt *rt, char *filename)
{
	int			ret;
	t_bufferio	*f;

	if (!ft_endwith(filename, ".rt"))
		return (NOT_RT_FILE);
	f = ft_open(open(filename, O_RDONLY), 1);
	if (!f)
		return (FAILED_OPEN);
	*rt = (t_minirt){};
	ret = load_rt_internal(rt, f);
	if (ret)
		del_rt(rt);
	ft_close(f, 1);
	return (ret);
}

static int	load_rt_internal(t_minirt *rt, t_bufferio *f)
{
	int			ret;
	char		*line;
	t_object	tmp;

	while (1)
	{
		if (ft_readline(&line, f))
			return (FAILED_ALLOCATE);
		if (!line)
			break ;
		ret = parse(line, &tmp);
		free(line);
		if (ret)
			return (ret);
		ret = set_rt(rt, &tmp);
		if (ret)
			return (ret);
	}
	return (NO_ERROR);
}

static int	set_rt(t_minirt *rt, t_object *object)
{
	if (object->type == o_none)
		return (NO_ERROR);
	if (object->type == o_ambient)
	{
		if (rt->ambient)
			return (MULTIPLE_DEFINED_AMBIENT);
		rt->ambient = ft_memdup(&object->value.ambient, sizeof(t_ambient));
		if (!rt->ambient)
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	if (object->type == o_camera)
	{
		if (rt->camera)
			return (MULTIPLE_DEFINED_CAMERA);
		rt->camera = ft_memdup(&object->value.camera, sizeof(t_camera));
		if (!rt->camera)
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	return (set_rt2(rt, object));
}

static inline int	set_rt2(t_minirt *rt, t_object *object)
{
	if (object->type == o_light)
	{
		if (ft_xlstappend(&rt->rights, &object->value.light, sizeof(t_light)))
			return (FAILED_ALLOCATE);
		return (NO_ERROR);
	}
	if (ft_xlstappend(&rt->figures, &object, sizeof(t_object)))
		return (FAILED_ALLOCATE);
	return (NO_ERROR);
}

void	del_rt(t_minirt *rt)
{
	free(rt->ambient);
	free(rt->camera);
	ft_xlstclear(&rt->rights);
	ft_xlstclear(&rt->figures);
}
