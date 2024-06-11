/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:35:41 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/11 20:38:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/renderer.h"
#include "rt2img.h"
#include "rt_errno.h"
#include <mlx.h>

/*
どういうアプローチをするか、
初期値: カメラのベクトル、反復0回

引数　今の色、視線、反復回数：
	もし、反復回数が上限ならば
		黒を返す。
	一番近い図形をもとめる。(scene_object_method)
		(交点情報：その座標での色など、)出射ベクトルをもとめる。
		反射率が０でなければ、再帰しその値に反射率を適応して、色を混ぜる。
		（カラーの反対色が吸収される）
	なければ
		黒にする。
	ambientを減算する
	全ての前方にある光源との
		距離を測る。間に図形があってはいけない。
		現在の色と距離で(1/2乗)減衰させて減算。
	結果を返す。
*/

int	renderer_render(t_renderer *self)
{
	void	*img;

	img = mlx_get_data_addr(self->img, &(int){0}, &(int){0}, &(int){0});
	rt2img(self->camera, self->objs, img);
	mlx_clear_window(self->mlx, self->win);
	mlx_put_image_to_window(self->mlx, self->win, self->img, 0, 0);
	return (NO_ERROR);
}
