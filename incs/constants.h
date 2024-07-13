/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:22:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/07/14 04:02:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <math.h>

# define USING "\
Usage: ./miniRT <rt-file>\n\
"

# define FORMAT_DESCRIPTION "\
rt-file format:\n\
\tAmbient\t\tA <ratio> <color>\n\
\tCamera\t\tC <coordinates> <orientation> <fov>\n\
\tLight\t\tL <coordinates> <brightness> <color>\n\
\n\
\tSphere\t\tsp <coordinates> <diameter> <color>\n\
\tPlane\t\tpl <coordinates> <orientation> <color>\n\
\tCylinder\tcy <coordinates> <axis> <diameter> <height> <color>\n\
\tTriangle\ttr <first> <second> <third> <color>\n\
"

# define KEY_OPERATION_DESCRIPTION "\
key operation:\n\
\tUp\tMove forward.\n\
\tDown\tMove backward.\n\
\tLeft\tMove left.\n\
\tRight\tMove right.\n\
\tz\tMove down.\n\
\tc\tMove up.\n\
\te\tRoll up.\n\
\tq\tRoll down.\n\
\tw\tPitch up.\n\
\ts\tPitch down.\n\
\ta\tYaw up.\n\
\td\tYaw down.\n\
\tk\tIncrease fov.\n\
\tj\tDecrease fov.\n\
\tr\tReturn to initial position.\n\
\tEsc\tClose window.\n\
"

# define ABOUT "\
Made by hshimizu.\n\
github\t: https://github.com/Neko-Sato\n\
profile\t: https://profile.intra.42.fr/users/hshimizu\n\
"

# ifndef ALLOW_MULTIPLE_CAMERAS
#  define ALLOW_MULTIPLE_CAMERAS 0
# endif

# ifndef ALLOW_MULTIPLE_AMIBIENTS
#  define ALLOW_MULTIPLE_AMIBIENTS 0
# endif

# ifndef ALLOW_MULTIPLE_LIGHTS
#  define ALLOW_MULTIPLE_LIGHTS 0
# endif

# ifndef ALLOW_FOV_UNLIMITED
#  define ALLOW_FOV_UNLIMITED 0
# endif

# ifndef ALTERNATIVE_UP_VECTOR
#  define ALTERNATIVE_UP_VECTOR 1
# endif

# define BVH_MAX_FIGURES 8

# define MAX_DIST INFINITY
# define MIN_DIST 0.0078125000

# define MAX_DEPTH 5

# define PIXELS_PER_DRAW 5000
# define PIXELS_PER_DRAW_PREVIEW 50000
# define MOVE_UNIT 1.0

#endif