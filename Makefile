# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuana <tjuana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/08 11:40:58 by tjuana            #+#    #+#              #
#    Updated: 2019/08/09 16:38:19 by tjuana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol

# src / obj files
SRC		= main.c \
		  events.c \
		  draw.c \
		  fractols1.c \
		  fractols2.c \
		  fractols3.c \
		  fractols4.c \
		  fractols5.c \
		  mouse.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Ofast -flto -march=native -Wall -Wextra -Werror

# mlx library
MLX		= ./minilibx/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx
MLX_LNK	= -L ./minilibx -l mlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft/includes
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./incl/
OBJDIR	= ./obj/

# colors
RED=\033[1;31m
GRE=\033[1;32m
LCY=\033[1;36m
LYE=\033[1;33m
NC=\033[0m

.PHONY: all, clean, fclean, re

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<
	@echo "${LCY} ┣╸ ${NC}$<" | sed 's/\.c/\.o/g'

$(FT_LIB):
	@make -C $(FT)
	@echo "${GRE}(✓) Libft${NC}"

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "${LYE}(✓) $(NAME)"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@make -C $(MLX) clean
	@echo "${RED}(✗) Objects${NC}"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(FT) fclean
	@echo "${RED}(✗) $(NAME)${NC}"

re: fclean all