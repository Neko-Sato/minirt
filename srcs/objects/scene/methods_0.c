/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:49:24 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/03 08:34:52 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/scene.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>

t_rt_errno	scene_load(t_scene *self, char *filename)
{
	t_rt_errno	ret;
	t_file		*f;
	char		*line;
	size_t		size;

	f = ft_file_new(open(filename, O_RDONLY), 0b10, 0, 1);
	if (!f)
		return (FAILED_OPEN);
	line = NULL;
	ret = SUCCESS;
	while (!ret && ft_getline(&line, &size, f) != -1)
		ret = parse_line(&(char *){line}, self);
	free(line);
	if (ret)
		return (ft_fclose(f), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), SUCCESS);
	return (ft_fclose(f), FAILED_ALLOCATE);
}
