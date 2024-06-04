/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:16:18 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/05 00:21:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT2IMG_H
# define RT2IMG_H

#include "objects/scene.h"

void	rt2img(t_scene *scene, unsigned int *img, int width, int height);

#endif
