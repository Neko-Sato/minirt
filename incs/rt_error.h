/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:17:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 10:05:21 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERROR_H
# define RT_ERROR_H

typedef enum e_rt_errno
{
	NO_ERROR,
	FAILED_ALLOCATE,
	NOT_RT_FILE,
	FAILED_OPEN,
	UNKNOW_IDENTIFIER,
	MULTIPLE_DEFINED_AMBIENT,
	UNDEFINED_AMBIENT,
	MULTIPLE_DEFINED_CAMERA,
	UNDEFINED_CAMERA,
	INCORRECT_FORMAT,
}					t_rt_errno;

extern const char	*g_rt_errmsg[];

void				put_rt_err(int rt_errno);

#endif
