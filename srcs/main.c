/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 05:37:42 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 22:32:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include "rt_errno.h"
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

/*
	Welcome to my wonderful code!
*/

static t_rt_errno	load(t_scene **scene, char *filename);
static t_rt_errno	internal(char *filename);

int	main(int argc, char *argv[])
{
	t_rt_errno	ret;

	ret = SUCCESS;
	if (argc == 1)
		minirt_put_using();
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = internal(argv[1]);
	if (!ret)
		return (EXIT_SUCCESS);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	rt_perror(ret);
	return (EXIT_FAILURE);
}

static t_rt_errno	load(t_scene **scene, char *filename)
{
	t_rt_errno	ret;
	t_scene		*tmp;
	char		*title;

	if (!ft_endwith(filename, ".rt"))
		return (NOT_RT_FILE);
	tmp = malloc(sizeof(t_scene));
	if (!tmp)
		return (FAILED_ALLOCATE);
	title = ft_strrchr(filename, '/');
	if (title)
		title++;
	else
		title = filename;
	ret = scene_init(tmp, &(t_scene_init){.title = title});
	if (ret)
		return (free(tmp), ret);
	ret = scene_load(tmp, filename);
	if (ret)
		return (scene_del(tmp), free(tmp), ret);
	*scene = tmp;
	return (SUCCESS);
}

static t_rt_errno	internal(char *filename)
{
	int			ret;
	t_scene		*scene;
	t_minirt	minirt;

	ret = load(&scene, filename);
	if (ret)
		return (ret);
	ret = minirt_init(&minirt, &(t_minirt_init){});
	if (ret)
		return (scene_del(scene), free(scene), ret);
	ret = minirt_add_scene(&minirt, scene);
	if (ret)
		return (scene_del(scene), free(scene), minirt_del(&minirt), ret);
	ret = minirt_loop(&minirt);
	return (minirt_del(&minirt), ret);
}
