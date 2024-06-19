/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 16:16:49 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errno.h"
#include <libft.h>
#include <unistd.h>

void	rt_perror(int rt_errno)
{
	static const char *const	rt_errmsg[] = {
		"Success.",
		"Unlikely error.",
		"Too many arguments.",
		"Failed allocate.",
		"Failed initialize mlx.",
		"Failed read.",
		"Not rt-file.",
		"Failed open.",
		"Unknown identifier.",
		"Multiple defined of ambient.",
		"Undefined of ambient.",
		"Multiple defined of camera.",
		"Undefined of camera.",
		"Incorrect format.",
		"Value is out of range.",
		"Ambiguous orientation.",
	};

	ft_putendl_fd((char *)rt_errmsg[rt_errno], STDERR_FILENO);
}
