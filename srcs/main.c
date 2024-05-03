/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:42:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 13:05:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_error.h"
#include <stdlib.h>
#include <unistd.h>

#define USING "\
Usage: ./miniRT <rt-file>\n\
\n\
rt-file format:\n\
\tAmbient\t\tA <ratio> <color>\n\
\tCamera\t\tC <coordinates> <orientation> <fov>\n\
\tLight\t\tL <coordinates> <brightness> <color>\n\
\n\
\tSphere\t\tsp <coordinates> <diameter> <color>\n\
\tPlane\t\tpl <coordinates> <normal> <color>\n\
\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n\
\n\
Made by hshimizu.\n\
github\t: https://github.com/Neko-Sato\n\
profile\t: https://profile.intra.42.fr/users/hshimizu\n\
"

int	main(int argc, char *argv[])
{
	int			ret;
	t_minirt	rt;

	if (argc < 2)
	{
		ft_putstr_fd(USING, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = load_rt(&rt, argv[1]);
	if (!ret)
		ret = NO_ERROR;
	if (ret)
	{
		put_rt_err(ret);
		return (EXIT_FAILURE);
	}
	del_rt(&rt);
	return (EXIT_SUCCESS);
}
