/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:16:54 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/03 18:25:19 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rt2img(t_minirt *rt, int size[2], unsigned int *img)
{
	int i;

	i = 0;
	(void)rt;
	while (i < size[0] * size[1])
	{
		if (i % size[0] == size[0] / 2)
			img[i] = 0xff0000;
		else if (i / size[0] == size[1] / 2)
			img[i] = 0x00ff00;
		else if (i / size[0] == i % size[0])
			img[i] = 0x0000ff;
		else
			img[i] = 0xffffff;
		i++;
	}
	return (0);
}