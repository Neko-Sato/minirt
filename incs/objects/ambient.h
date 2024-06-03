/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:13:17 by hshimizu          #+#    #+#             */
/*   Updated: 2024/06/02 03:35:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include <libft.h>

typedef struct s_ambient		t_ambient;

typedef struct s_class_ambient
{
	int							(*init)(t_ambient *self);
	void						(*del)(t_ambient *self);
}								t_class_ambient;

int								__ambient_init(t_ambient *self);
void							__ambient_del(t_ambient *self);

extern const t_class_ambient	g_class_ambient;

typedef struct s_ambient
{
	const t_class_ambient		*__class;
	double						ratio;
	t_color						color;
}								t_ambient;

#endif
