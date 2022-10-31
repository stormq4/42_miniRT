# -*- Makefile -*-

## EXECUTABLE NAMES
F_NAME :=				lexer \
						parser \
						expander

EXEC_DIR :=				tests
NAME :=					$(addprefix $(EXEC_DIR)/, $(F_NAME))

## INCLUDES
INC_UT := 				-I ../inc
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

## COMMANDS
test : $(NAME)
	@mkdir -p $(dir $@)
	@rm -rf $(EXEC_DIR)/lexer.dSYM $(EXEC_DIR)/parser.dSYM $(EXEC_DIR)/expander.dSYM
	@./run_test.sh

all : $(NAME)
	@mkdir -p $(dir $@)
	@rm -rf $(EXEC_DIR)/lexer.dSYM $(EXEC_DIR)/parser.dSYM

$(NAME) : $(LIBA) $(OBJ)

fclean :
	@rm -rf $(EXEC_DIR) results
	@echo $(RED) "Deleting TESTER Executable [OK]"

$(LIBA) :
	@$(MAKE) -C $(LIBFT) bonus

$(OBJ_DIR)/%.o : ../%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_UT) -c $< -o $@

$(EXEC_DIR)/% : src/%$(_)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJ) $(SRC_UNITC) $(UNIT_INC) $(UNITY_DEFINES) $(INC_UT) $(LIBA) $(READLINE) $(SANITIZE) $< -o $@
