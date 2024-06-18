# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 03:21:14 by hshimizu          #+#    #+#              #
#    Updated: 2024/06/19 02:52:20 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:= $(shell uname)

NAME		:= miniRT

DIR			:= .
FT			:= $(DIR)/libft
MLX			:= $(DIR)/libmlx
INCS_DIR	:= $(DIR)/incs
SRCS_DIR	:= $(DIR)/srcs
OUT_DIR		:= $(DIR)/out
TEST_RT		:= $(DIR)/scene/test.rt

SRCS		:= \
	$(addprefix $(SRCS_DIR)/, \
		$(addprefix objects/, \
			minirt_0.c \
			minirt_1.c \
			scene_0.c \
			scene_1.c \
			renderer_0.c \
			renderer_1.c \
			renderer_2.c \
			renderer_3.c \
			ambient_0.c \
			camera_0.c \
			light_0.c \
			figure_0.c \
			sphere_0.c \
			plane_0.c \
			cylinder_0.c \
			square_0.c \
			triangle_0.c \
		) \
		$(addprefix parsers/, \
			token_basic_0.c \
			token_basic_1.c \
			token_basic_2.c \
			token.c \
			token_optional.c \
			token_ambient.c \
			token_camera.c \
			token_light.c \
			token_sphere.c \
			token_plane.c \
			token_cylinder.c \
			token_square.c \
			token_triangle.c \
		) \
		$(addprefix utils/, \
			vec3d_operator.c \
			vec3d_basic.c \
			matrix3x3_operator.c \
			matrix3x3_rotation.c \
		) \
		main.c \
		rt_errno.c \
		rt2img_test.c \
	)

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g -fsanitize=address -D ALLOW_MULTIPLE_CAMERAS=1 -D ALLOW_FOV_UNLIMITED=1
IDFLAGS		:= -I$(INCS_DIR) -I$(FT) -I$(MLX)
LDFLAGS		:= -L$(FT) -L$(MLX)
LIBS		:= -lft -Wl,-rpath ./libft -lmlx -lm -lX11 -lXext
ifeq ($(UNAME), Darwin)
LDFLAGS		+= -L/usr/X11/lib
IDFLAGS		+= -I/usr/X11/include
LIBS		+= -framework OpenGL -framework AppKit
endif

.PHONY: all clean fclean re bonus

all: $(FT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

bonus: all

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -MMD -MP $(IDFLAGS) $< -o $@

clean:
	$(RM) -r $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: test
test: $(NAME) $(TEST_RT)
	@lldb -o r -- $< $(TEST_RT)

.PHONY: norm norm-upgrade
norm: $(SRCS) $(INCS_DIR)
	# @make -C $(FT) norm
	@norminette $^

norm-upgrade:
	@python3 -m pip install --upgrade norminette

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@ libft.a

.PHONY: $(MLX)
$(MLX):
	@git submodule update --init $@
	@$(MAKE) -C $@

-include $(DEPS)
