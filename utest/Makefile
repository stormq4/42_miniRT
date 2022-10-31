# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sde-quai <sde-quai@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/28 10:05:21 by sde-quai      #+#    #+#                  #
#    Updated: 2022/10/25 09:14:30 by sde-quai      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

include ../Pretty.mk

## EXECUTABLE NAMES
F_NAME :=				parser

EXEC_DIR :=				tests
NAME :=					$(addprefix $(EXEC_DIR)/, $(F_NAME))

## INCLUDES
INC_UT := 				-I ../inc -I ../MLX42/include/MLX42
UNIT_INC := 			-I ./inc

## UNITY DEFINES
UNITY_DEFINES 			:=
#  -D UNITY_OUTPUT_COLOR

## LIBFT
LIBFT :=				../libft
LIBA :=					../libft/libft.a

## SRCS FILES
_ := 					_test.c
SRC_UT :=				$(addsuffix $(_), $(addprefix src/, $(F_NAME)))

SRC_UNITC := 			unity/src/unity.c

## SANITIZE
SANITIZE := 			-fsanitize=address

## OBJECT FILES
OBJ_DIR :=				../obj
OBJ := 					$(addprefix $(OBJ_DIR)/, $(SRC_TEST:%.c=%.o))

MLX :=					$(addprefix ../, $(MLX))

## COMMANDS
test : $(NAME)
	@mkdir -p $(dir $@)
	@rm -rf $(EXEC_DIR)/parser.dSYM
	@./run_test.sh
	@rm tests/errors.txt

all : $(NAME)
	@mkdir -p $(dir $@)
	@rm -rf $(EXEC_DIR)/parser.dSYM

$(NAME) : $(LIBA) $(MLX) $(OBJ)

$(MLX) :
	@$(MAKE) -C ../MLX42

fclean :
	$(RM) $(EXEC_DIR) results
	$(TEST_FCLEAN)

$(LIBA) :
	@$(MAKE) -C $(LIBFT) bonus

$(OBJ_DIR)/%.o : ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(BONUS) $(INC_UT) -c $< -o $@

$(EXEC_DIR)/% : src/%$(_)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJ) $(SRC_UNITC) $(UNIT_INC) $(UNITY_DEFINES) $(INC_UT) $(MLX) $(MLX_FLAGS) $(LIBA) $(SANITIZE) $< -o $@
