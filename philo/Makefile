# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 20:51:21 by aquinter          #+#    #+#              #
#    Updated: 2024/06/18 21:19:27 by aquinter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wextra -Werror -Wall -fsanitize=address
IFLAGS = -I$(INC_DIR)

OBJ_DIR = obj/
INC_DIR	= inc/
SRC_DIR = src/

RM = rm -rf

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR), $(SRC:$(SRC_DIR)%.c=%.o))

TOTAL_FILES = $(words $(SRC))

CURRENT_FILES = 0

define progress_bar
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @printf "\rCompiling Philosophers... [%-$(TOTAL_FILES)s] %-10s%d%%" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) "" $(shell echo $$((($(CURRENT_FILE) * 100) / $(TOTAL_FILES))))
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
				$(call progress_bar)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned philosophers objects"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
