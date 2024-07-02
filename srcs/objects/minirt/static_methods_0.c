/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_methods_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:27:48 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/02 22:16:23 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/minirt.h"
#include <unistd.h>

void	minirt_put_using(void)
{
	ft_putendl_fd(USING, STDERR_FILENO);
	ft_putendl_fd(FORMAT_DESCRIPTION, STDERR_FILENO);
	ft_putendl_fd(KEY_OPERATION_DESCRIPTION, STDERR_FILENO);
	ft_putstr_fd(ABOUT, STDERR_FILENO);
}
