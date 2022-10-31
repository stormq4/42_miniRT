# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sde-quai <sde-quai@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/27 09:59:09 by sde-quai      #+#    #+#                  #
#    Updated: 2022/10/26 13:58:05 by sde-quai      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

include Pretty.mk

## Executable for minishell
NAME =					 miniRT


## Flags and Compilers
CFLAGS = 				-Wall -Wextra -Werror -g

ifdef sanitize

CFLAGS := 				-Wall -fsanitize=address -Wextra -g
# CFLAGS := 				-Wall -fsanitize=thread -Wextra -g

endif

ifdef bonus
export BONUS =			-D RT_BONUS=1
else
export BONUS = 			-D RT_BONUS=0
endif


## MLX
export MLX := 			MLX42/libmlx42.a
export MLX_FLAGS :=		-lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

## Headerfiles
INC :=					-I ./inc -I ./MLX42/include/MLX42

INLCUDES =				mini_rt.h \
						libft.h \
						vec4.h \
						utils.h \
						get_next_line.h \
						parser.h \
						rays.h


INLCUDES := 			$(addprefix inc/, $(INLCUDES))

## Libft
LIBFT := 				libft
LIBA := 				libft/libft.a


## Source files

# directory
DIR_SRC :=				src

MAIN :=					main.c

C_FILES :=				init_screen.c \
						utils/verify_input.c \
						utils/utils.c \
						utils/vector_get.c \
						utils/get_rgba.c \
						parser/free_input.c \
						parser/parser.c \
						parser/p_utils.c \
						parser/utils_vec.c \
						parser/tokens.c \
						parser/add_sources.c \
						parser/add_objects.c \
						rays/camera.c \
						rays/threads.c \
						rays/plane.c \
						rays/shoot.c \
						rays/sphere.c \
						rays/light.c \
						rays/light_2.c \
						rays/cylinder.c \
						rays/cylinder_utils.c 
						
SRC_MAIN :=				$(addprefix $(DIR_SRC)/, $(MAIN))

export SRC_TEST :=		$(addprefix $(DIR_SRC)/, $(C_FILES))  

## All Source Files in variable
SRC :=					$(SRC_MAIN) $(SRC_TEST)

## Object files from source files
OBJ_DIR :=				obj
OBJ_C :=				$(addprefix $(OBJ_DIR)/, $(SRC))
OBJ :=					$(OBJ_C:%.c=%.o)

## Commands
all : $(NAME)

utest : fclean
	@$(MAKE) -C utest test


$(MLX) : 
	$(COMP_MLX)
	@$(MAKE) -C MLX42
	$(MLX_COMPILED)

$(LIBA) :
	@$(MAKE) -C $(LIBFT) bonus

$(NAME) : $(LIBA) $(OBJ) $(INLCUDES) $(MLX)
	$(O_FILES_P)
	$(CC) $(CFLAGS) $(INC) $(BONUS) $(LIBA) $(OBJ) $(MLX) $(MLX_FLAGS) -o $(NAME)
	$(EXEC_CREATE_P)

sanitize : clean
	$(MAKE) sanitize=1
	$(EXEC_SANITIZE_P)

bonus : clean
	$(MAKE) bonus=1

$(OBJ_DIR)/%.o : %.c $(INLCUDES)
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(BONUS) -c $< -o $@

clean :
	$(RM) $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C MLX42
	$(CLEAN_P)

fclean : clean
	@$(MAKE) fclean -C $(LIBFT)
	@$(MAKE) fclean -C utest
	@$(MAKE) fclean -C MLX42
	$(RM) $(NAME) miniRT.dSYM
	$(FCLEAN_P)

re : fclean all

.PHONY: all, clean, fclean, re
