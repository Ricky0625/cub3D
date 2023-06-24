# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 14:14:36 by wricky-t          #+#    #+#              #
#    Updated: 2023/06/24 13:26:27 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

NAME		:= cub3D

CC			:= gcc

CFLAGS		:= -Wall -Werror -Wextra $(INCFLAGS)

ifeq ($(DB), 1)
	CFLAGS += -fsanitize=address -g3
endif

SRC_PATH	:= srcs

OBJ_PATH	:= objs

LIBFT		:= lib42

MLX			:= mlx

INCLUDES	:= includes

INCFLAGS	:= -I $(INCLUDES) -I $(LIBFT) -I $(MLX)

CFLAGS		+= $(INCFLAGS)

STATLIB		:= $(LIBFT)/*.a

MLXFLAGS	:= -L$(MLX) -l$(MLX) -framework OpenGL -framework AppKit

RM			:= rm -rf

NORM		:= norminette

UNAME		:= $(shell uname)

ifeq ($(UNAME), Linux)
	MLXFLAGS	:= -Lmlx_linux -lmlx_Linux -L/usr/lib -I/usr/include -Imlx_linux -lXext -lX11 -lm -lz
	CFLAGS		+= -I/usr/include -Imlx_linux -03
endif

#------------------------------------------------------------------------------#
#   PROGRAM'S SCRS                                                             #
#------------------------------------------------------------------------------#

SRCS		:= cub3d.c \
			   init/init_textures.c init/init_player.c init/init_raycaster.c \
			   hooks/hook.c hooks/key_hook.c \
			   parsing/parse_map.c parsing/parse_elements.c parsing/parse_check.c \
			   controls/player_movement.c controls/controls.c controls/mouse_control.c \
			   raycasting/get_rays.c raycasting/get_rays_utils.c \
			   minimap/minimap.c \
			   utils/error.c utils/img_utils.c utils/color_utils.c utils/draw_utils.c utils/map_utils.c utils/math_utils.c \

SRCS		:= $(SRCS:%=$(SRC_PATH)/%)

OBJS		:= $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

#------------------------------------------------------------------------------#
#   STYLING                                                                    #
#------------------------------------------------------------------------------#

GR			:= \033[1;92m

BL			:= \033[1;34m

UBL			:= \033[4;34m

YL			:= \033[1;33m

DF			:= \033[0m

#------------------------------------------------------------------------------#
#   RECIPE                                                                     #
#------------------------------------------------------------------------------#

all: $(NAME)
	@clear
	@echo ""
	@echo "      ┏━━━┳┓╋┏┳━━┓┏━━━┳━━━┓"
	@echo "      ┃┏━┓┃┃╋┃┃┏┓┃┃┏━┓┣┓┏┓┃"
	@echo "      ┃┃╋┗┫┃╋┃┃┗┛┗╋┛┏┛┃┃┃┃┃"
	@echo "      ┃┃╋┏┫┃╋┃┃┏━┓┣┓┗┓┃┃┃┃┃"
	@echo "      ┃┗━┛┃┗━┛┃┗━┛┃┗━┛┣┛┗┛┃"
	@echo "      ┗━━━┻━━━┻━━━┻━━━┻━━━┛"
	@echo ""

ifeq ($(DB), 1)
	@echo "$(YL)"
	@echo "	   DEBUG MODE"
	@echo "$(DF)"
endif

$(NAME): $(OBJS)
	@echo "$(GR)Patching everything...$(DF)"
	@make bonus -C $(LIBFT)
	@$(CC) $(CFLAGS) $(MLXFLAGS) $^ $(STATLIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BL)↻ Compiling $(UBL)$(notdir $<)$(DF)"

help:
	@clear
	@echo "Help"

clean:
	@clear
	@make clean -C $(LIBFT)
	@$(RM) $(OBJ_PATH)
	@echo "$(YL)✗ Removed $(OBJ_PATH)$(DF)"

fclean: clean
	@make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(YL)✗ Removed $(NAME)$(DF)"

re: fclean all

norm: $(SRCS)
	@reset
	@$(NORM) $(SRCS) $(INCLUDES) $(LIBFT)

.PHONY:
	clean fclean re
