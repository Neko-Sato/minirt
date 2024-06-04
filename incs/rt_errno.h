/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 07:42:01 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRNO_H
# define RT_ERRNO_H

typedef enum e_rt_errno
{
	NO_ERROR,
	UNLIKELY_ERROR,
	TOO_MANY_ARGUMENTS,
	FAILED_ALLOCATE,
	FAILED_INITIALIZE_MLX,
	FAILED_READ,
	NOT_RT_FILE,
	FAILED_OPEN,
	UNKNOW_IDENTIFIER,
	MULTIPLE_DEFINED_AMBIENT,
	UNDEFINED_AMBIENT,
	MULTIPLE_DEFINED_CAMERA,
	UNDEFINED_CAMERA,
	INCORRECT_FORMAT,
	OUT_OF_RANGE,
	AMBIGUOUS_ORIENTATION,
}		t_rt_errno;

void	rt_perror(int rt_errno);

#endif
