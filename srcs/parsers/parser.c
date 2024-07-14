/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:15:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 06:23:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/camera.h"
#include "objects/abstract_light.h"
#include "objects/abstract_figure.h"
#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>

static void	clear_context(t_parser *context);

t_rt_errno	parser(const char *filename, t_parser *context)
{
	t_rt_errno	ret;
	t_file		*f;
	char		*line;
	size_t		size;

	*context = (t_parser){};
	f = ft_file_new(open(filename, O_RDONLY), 0b10, 0, 1);
	if (!f)
		return (FAILED_OPEN);
	line = NULL;
	ret = SUCCESS;
	while (!ret && ft_getline(&line, &size, f) != -1)
		ret = parse_line(&(char *){line}, context);
	free(line);
	if (ret)
		return (ft_fclose(f), clear_context(context), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), clear_context(context), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), SUCCESS);
	return (ft_fclose(f), clear_context(context), FAILED_ALLOCATE);
}

static void	clear_context(t_parser *context)
{
	void	*tmp;

	while (ft_xlstpop(&context->cameras, 0, &tmp, sizeof(tmp)) != -1)
		(void)(camera_del(tmp), free(tmp));
	while (ft_xlstpop(&context->lights, 0, &tmp, sizeof(tmp)) != -1)
		(void)(((t_abstract_light *)tmp)->_->del(tmp), free(tmp));
	while (ft_xlstpop(&context->figures, 0, &tmp, sizeof(tmp)) != -1)
		(void)(((t_abstract_figure *)tmp)->_->del(tmp), free(tmp));
	*context = (t_parser){};
}
