/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:15:23 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 03:20:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt_errno.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>

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
		return (ft_fclose(f), ret);
	if (ft_ferror(f))
		return (ft_fclose(f), FAILED_READ);
	if (ft_feof(f))
		return (ft_fclose(f), SUCCESS);
	return (ft_fclose(f), FAILED_ALLOCATE);
}
