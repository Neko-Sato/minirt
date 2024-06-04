/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:37:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 05:25:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <stdlib.h>

static int	load(t_scene **scene, char *filename);
static int	internal(char *filename);

int	main(int argc, char *argv[])
{
	int	ret;

	if (argc == 1)
	{
		minirt_put_using();
		return (EXIT_SUCCESS);
	}
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = internal(argv[1]);
	if (ret)
	{
		rt_perror(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	load(t_scene **scene, char *filename)
{
	int		ret;
	t_scene	*tmp;
	char	*title;

	if (!ft_endwith(filename, ".rt"))
		return (NOT_RT_FILE);
	tmp = malloc(sizeof(t_scene));
	if (!tmp)
		return (FAILED_ALLOCATE);
	title = ft_strchr(filename, '/');
	if (title)
		title++;
	else
		title = filename;
	ret = scene_init(tmp, title);
	if (ret)
		return (free(tmp), ret);
	ret = scene_load(tmp, filename);
	if (ret)
		return (scene_del(tmp), free(tmp), ret);
	*scene = tmp;
	return (NO_ERROR);
}

static int	internal(char *filename)
{
	int			ret;
	t_scene		*scene;
	t_minirt	minirt;

	ret = load(&scene, filename);
	if (ret)
		return (ret);
	ret = minirt_init(&minirt, scene);
	if (ret)
		return (scene_del(scene), free(scene), ret);
	ret = minirt_show(&minirt);
	minirt_del(&minirt);
	return (ret);
}
