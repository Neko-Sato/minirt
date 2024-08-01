/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:22:38 by hshimizu          #+#    #+#             */
/*   Updated: 2024/08/01 22:34:02 by hshimizu         ###   ########.fr       */
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
\tCone\t\tcn <coordinates> <diameter> <apex> <color>\n\
"

# define KEY_OPERATION_DESCRIPTION "\
key operation:\n\
\tw\tMove forward.\n\
\ts\tMove backward.\n\
\ta\tMove left.\n\
\td\tMove right.\n\
\tc\tMove up.\n\
\tz\tMove down.\n\
\te\tRoll up.\n\
\tq\tRoll down.\n\
\tUp\tPitch up.\n\
\tDown\tPitch down.\n\
\tLeft\tYaw up.\n\
\tRight\tYaw down.\n\
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

# define BVH_MAX_FIGURES 20

# define MAX_DIST __FLT_MAX__
# define MIN_DIST 0.0078125000

# define MAX_DEPTH 8

# define PIXELS_PER_DRAW 2500
# define PIXELS_PER_DRAW_PREVIEW 5000
# define MOVE_UNIT 1.
# define ROTATE_UNIT 0.017453292519943295

#endif