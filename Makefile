# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 03:21:14 by hshimizu          #+#    #+#              #
#    Updated: 2024/07/26 04:23:15 by hshimizu         ###   ########.fr        #
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
TEST_RT		:= $(DIR)/scenes/test.rt

SRCS		:= \
	$(addprefix $(SRCS_DIR)/, \
		$(addprefix objects/, \
			$(addprefix minirt/, \
				methods_0.c \
				methods_1.c \
				special.c \
				static_methods_0.c \
			) \
			$(addprefix bvh/, \
				static_methods_0.c \
			) \
			$(addprefix bvh_inner/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix bvh_leaf/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix scene/, \
				methods_0.c \
				static_methods_0.c \
				special.c \
			) \
			$(addprefix renderer/, \
				methods_0.c \
				methods_1.c \
				methods_2.c \
				methods_3.c \
				methods_4.c \
				special.c \
			) \
			$(addprefix abstract_figure/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix abstract_light/, \
				special.c \
			) \
			$(addprefix ambient/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix camera/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix light/, \
				methods_0.c \
				special.c \
			) \
			$(addprefix sphere/, \
				methods_0.c \
				methods_1.c \
				special.c \
			) \
			$(addprefix plane/, \
				methods_0.c \
				methods_1.c \
				special.c \
			) \
			$(addprefix cylinder/, \
				methods_0.c \
				methods_1.c \
				special.c \
			) \
			$(addprefix triangle/, \
				methods_0.c \
				methods_1.c \
				special.c \
			) \
			$(addprefix cone/, \
				methods_0.c \
				methods_1.c \
				special.c \
			) \
		) \
		$(addprefix parsers/, \
			parser.c \
			token.c \
			token_basic_0.c \
			token_basic_1.c \
			token_utils.c \
			token_ambient.c \
			token_camera.c \
			token_light.c \
			token_sphere.c \
			token_plane.c \
			token_cylinder.c \
			token_triangle.c \
			token_cone.c \
		) \
		$(addprefix utils/, \
			vec3_basic.c \
			vec3_operator.c \
			vec3_utils.c \
			mat3x3_operator.c \
			mat3x3_rotation.c \
			mat3x3_transform.c \
			mat3x3_utils.c \
			aabb.c \
		) \
	main.c \
	rt_errno.c \
	) 

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CFLAGS		:= -Wall -Wextra -Werror
CFLAGS		+= -Ofast
# CFLAGS		+= -g -fsanitize=address
CFLAGS		+= -D ALLOW_MULTIPLE_CAMERAS=1
CFLAGS		+= -D ALLOW_MULTIPLE_AMIBIENTS=1
CFLAGS		+= -D ALLOW_MULTIPLE_LIGHTS=1
# CFLAGS		+= -D ALLOW_FOV_UNLIMITED=1
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
	@make -C $(FT) norm
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
