/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:37:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:33:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Welcome to my wonderful code!
*/

static t_rt_errno	internal(char *filenames[]);
static t_rt_errno	load(t_minirt *minirt, char *filenames[]);

int	main(int argc, char *argv[])
{
	t_rt_errno	ret;

	ret = SUCCESS;
	if (argc == 1)
		minirt_put_using();
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = internal(&argv[1]);
	if (!ret)
		return (EXIT_SUCCESS);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	rt_perror(ret);
	return (EXIT_FAILURE);
}

static t_rt_errno	internal(char *filenames[])
{
	int			ret;
	t_minirt	minirt;

	ret = minirt_init(&minirt, &(t_minirt_init){});
	if (ret)
		return (ret);
	ret = load(&minirt, filenames);
	if (ret)
		return (minirt_del(&minirt), ret);
	ret = minirt_loop(&minirt);
	return (minirt_del(&minirt), ret);
}

static t_rt_errno	load(t_minirt *minirt, char *filenames[])
{
	t_rt_errno	ret;
	t_scene		*scene;

	while (*filenames)
	{
		scene = malloc(sizeof(*scene));
		if (!scene)
			return (FAILED_ALLOCATE);
		ret = scene_load(scene, *filenames++);
		if (ret)
			return (free(scene), ret);
		ret = minirt_add_scene(minirt, scene);
		if (ret)
			return (scene_del(scene), free(scene), ret);
	}
	return (SUCCESS);
}
