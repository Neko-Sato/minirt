/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/27 02:23:27 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRNO_H
# define RT_ERRNO_H

/*
	Errors?
	I don't want any of that to happen...
	In other words, they don't go! Segfault or...
*/

typedef enum e_rt_errno
{
	SUCCESS,
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

void	rt_perror(t_rt_errno rt_errno);

#endif
