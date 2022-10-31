# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sde-quai <sde-quai@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/09/27 14:55:13 by sde-quai      #+#    #+#                  #
#    Updated: 2022/10/03 14:57:50 by sde-quai      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

include ../Pretty.mk

NAME := libft.a

CFLAGS := -Wall -Wextra -Werror

CC := gcc

SRCS := \
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_check_malloc.c \
ft_split_utils.c \
absolute.c \
get_next_line.c \
get_next_line_utils.c


SRCS_BONUS := \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c

OBJS := ${SRCS:%.c=%.o}

OBJS_BONUS := ${SRCS_BONUS:%.c=%.o}

HEADFILES := libft.h

ifdef EXEC_BONUS
ALL_OBJS = $(OBJS) $(OBJS_BONUS)
else
ALL_OBJS = $(OBJS)
endif

RED :=		"\033[1;31m"
GREEN :=	"\033[1;32m"
CYAN :=		"\033[1;36m"
END :=		"\033[0m" 

all : $(NAME) 

%.o : %.c $(HEADFILES)
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME): $(ALL_OBJS)
	@echo $(GREEN)"Object files created for LIBFT [OK]"$(END)
	@ar -ru $(NAME) $^

bonus:
	@$(MAKE) EXEC_BONUS=1

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo $(RED)"Deleting object files from libft [OK]"$(END)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"Deleting library file libft.a [OK]"$(END)

re: fclean all

.PHONY: all, clean, fclean, re, bonus
