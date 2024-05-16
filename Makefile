# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 03:21:14 by hshimizu          #+#    #+#              #
#    Updated: 2024/05/16 09:45:37 by hshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT

DIR			:= .
FT			:= $(DIR)/libft
MLX			:= $(DIR)/libmlx
INCS_DIR	:= $(DIR)/incs
SRCS_DIR	:= $(DIR)/srcs
OUT_DIR		:= $(DIR)/out

SRCS		:= \
	$(addprefix $(SRCS_DIR)/, \
		main.c \
		minirt.c \
		rt_errno.c \
		scene.c \
		object.c \
		$(addprefix objects/, \
			o_ambient.c \
			o_camera.c \
			o_light.c \
			o_figure.c \
		) \
		figure.c \
		$(addprefix figures/, \
			f_spere.c \
			f_plane.c \
			f_cylinder.c \
		) \
	texture.c \
		$(addprefix textures/, \
			t_simple.c \
		) \
		parser.c \
		parser2.c \
		rt2img.c \
		$(addprefix utils/, \
			vec3d.c \
			vec3d2.c \
		) \
	)

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -g
IDFLAGS		:= -I$(INCS_DIR) -I$(FT) -I$(MLX)
LDFLAGS		:= -L$(FT) -L$(MLX)
LIBS		:= -lft -lmlx -lm -lXext -lX11

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
test: test.c $(OBJS)
	$(CC) -g -fsanitize=address $(LDFLAGS) $(IDFLAGS) $^ -o $@ $(LIBS)

.PHONY: norm norm-upgrade
norm: $(SRCS) $(INCS_DIR)
	# @make -C $(FT) norm
	@norminette $^

norm-upgrade:
	@python3 -m pip install --upgrade norminette

.PHONY: $(FT)
$(FT):
	#@git submodule update --init $@
	@$(MAKE) -C $@

.PHONY: $(MLX)
$(MLX):
	@git submodule update --init $@
	@$(MAKE) -C $@

-include $(DEPS)
