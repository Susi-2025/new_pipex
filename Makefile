# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 16:05:03 by vinguyen          #+#    #+#              #
#    Updated: 2025/07/23 16:32:40 by vinguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = .
OBJ_DIR = Object

LIBFT_DIR = libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

SRC =	0_pipex.c \

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(OBJ_DIR) $(LIBFT_NAME) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#Build library
$(LIBFT_NAME): $(LIBFT_OBJ)
	ar rcs $@ $^

#Compile library object files
$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#Compile project obj files into Object folder
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Build final executable
$(NAME): $(OBJ) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_NAME) -o $(NAME)

#cleaning
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIBFT_OBJ)

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re
