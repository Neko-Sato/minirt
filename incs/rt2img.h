/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:16:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/19 19:53:24 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT2IMG_H
# define RT2IMG_H

# include "objects/scene.h"
# include "utils/ray.h"

t_color	rt2img(t_rtobjs *objs, t_ray *r, int max_depth);

t_color	rt2img_test1(t_ray *r);
t_color	rt2img_test2(t_ray *r);

#endif
