/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_figure.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 02:16:57 by hshimizu          #+#    #+#             */
/*   Updated: 2024/05/16 09:30:38 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef O_FIGURE_H
# define O_FIGURE_H

# include "figure.h"

# define IDENTIFIER_O_FIGURE "F"

typedef struct s_o_figure
{
	t_figure			figure;
}						t_o_figure;

typedef struct s_object	t_object;

int						o_figure_parser(char *str, t_object *object);

#endif
