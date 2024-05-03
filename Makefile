# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 03:21:14 by hshimizu          #+#    #+#              #
#    Updated: 2024/05/03 12:26:49 by hshimizu         ###   ########.fr        #
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
		objects.c \
		minirt.c \
		rt_error.c \
		parse.c \
		parse_entry1.c \
		parse_entry2.c 	\
		vec3d.c \
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

.PHONY: norm
norm: $(SRCS) $(INCS_DIR)
	@make -C $(FT) norm
	@norminette $^

.PHONY: $(FT)
$(FT):
	@git submodule update --init $@
	@$(MAKE) -C $@

.PHONY: $(MLX)
$(MLX):
	@git submodule update --init $@
	@$(MAKE) -C $@

-include $(DEPS)
