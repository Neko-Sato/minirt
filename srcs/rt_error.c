/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:49:19 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 12:59:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"
#include <libft.h>
#include <unistd.h>

const char	*g_rt_errmsg[] = {
	"No error.",
	"Too many arguments.",
	"Failed allocate.",
	"Failed initialize mlx.",
	"Not rt-file.",
	"Failed open.",
	"Unknown identifier.",
	"Multiple defined of ambient.",
	"Undefined of ambient.",
	"Multiple defined of camera.",
	"Undefined of camera.",
	"Incorrect format.",
};

void	put_rt_err(int rt_errno)
{
	ft_putstr_fd((char *)g_rt_errmsg[rt_errno], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
