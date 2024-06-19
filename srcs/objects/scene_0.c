/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:18:32 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:14:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <stdlib.h>

int	scene_init(t_scene *self, char *title)
{
	*self = (t_scene){};
	ft_strlcpy(self->title, title, sizeof(self->title));
	return (SUCCESS);
}

void	scene_del(t_scene *self)
{
	void	*tmp;

	while (ft_xlstpop(&self->objs.ambients, 0, &tmp, sizeof(t_ambient *)) != -1)
		(void)(ambient_del((t_ambient *)tmp), free(tmp));
	while (ft_xlstpop(&self->cameras, 0, &tmp, sizeof(t_camera *)) != -1)
		(void)(camera_del((t_camera *)tmp), free(tmp));
	while (ft_xlstpop(&self->objs.lights, 0, &tmp, sizeof(t_light *)) != -1)
		(void)(light_del((t_light *)tmp), free(tmp));
	while (ft_xlstpop(&self->objs.figures, 0, &tmp, sizeof(t_figure *)) != -1)
		(void)(((t_figure *)tmp)->_->del(((t_figure *)tmp)), free(tmp));
}

int	scene_load(t_scene *self, char *filename)
{
	int		ret;
	t_file	*f;
	char	*line;
	size_t	size;
	char	*s;

	f = ft_file_new(open(filename, O_RDONLY), 0b10, 0, 1);
	if (!f)
		return (FAILED_OPEN);
	line = NULL;
	while (ft_getline(&line, &size, f) > 0)
	{
		s = line;
		ret = parse_line(&s, self);
		if (ret)
			break ;
	}
	free(line);
	if (ret)
		return (ft_fclose(f), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), SUCCESS);
	return (ft_fclose(f), FAILED_ALLOCATE);
}
