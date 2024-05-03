/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:42:22 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 18:07:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_error.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600

static int	internal(char *filename);

int	main(int argc, char *argv[])
{
	int	ret;

	if (argc < 2)
	{
		ft_putstr_fd(USING, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (2 < argc)
		ret = TOO_MANY_ARGUMENTS;
	else
		ret = internal(argv[1]);
	if (ret)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		put_rt_err(ret);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	internal(char *filename)
{
	int			ret;
	void		*mlx;
	void		*win;
	t_minirt	rt;

	mlx = mlx_init();
	if (!mlx)
		return (FAILED_INITIALIZE_MLX);
	ret = load_rt(&rt, filename);
	if (ret == NO_ERROR)
	{
		win = show_rt(&rt, mlx, filename, (int []){WIDTH_SIZE, HEIGHT_SIZE});
		if (!win)
			ret = FAILED_ALLOCATE;
		else
			mlx_loop(mlx);
	}
	mlx_destroy_display(mlx);
	free(mlx);
	return (ret);
}
