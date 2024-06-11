# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 03:21:14 by hshimizu          #+#    #+#              #
#    Updated: 2024/06/11 20:36:58 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
			minirt.c \
			minirt2.c \
			scene.c \
			scene2.c \
			renderer.c \
			renderer2.c \
			renderer3.c \
			renderer4.c \
			renderer5.c \
			ambient.c \
			camera.c \
			light.c \
			figure.c \
			sphere.c \
			plane.c \
			cylinder.c \
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
		) \
		$(addprefix utils/, \
			vec3d.c \
			vec3d2.c \
			matrix3x3.c \
			matrix3x3_rotation.c \
		) \
		main.c \
		rt_errno.c \
		rt2img.c \
	)

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g -fsanitize=address
IDFLAGS		:= -I$(INCS_DIR) -I$(FT) -I$(MLX)
LDFLAGS		:= -L$(FT) -L$(MLX)
LIBS		:= -lft -Wl,-rpath ./libft -lmlx -lm -lXext -lX11

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
	@lldb $< $(TEST_RT) -o r

.PHONY: norm norm-upgrade
norm: $(SRCS) $(INCS_DIR)
	# @make -C $(FT) norm
	@norminette $^

norm-upgrade:
	@python3 -m pip install --upgrade norminette

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

.PHONY: $(MLX)
$(MLX):
	@git submodule update --init $@
	@$(MAKE) -C $@

-include $(DEPS)
