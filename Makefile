# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 16:06:54 by apercebo          #+#    #+#              #
#    Updated: 2022/06/23 15:28:20 by dbouron          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#### LISTES ####

SOURCES = main.c \
		  parsing.c \
		  environnement.c \
		  error.c \
		  cmd_lst_utils1.c \
		  cmd_lst_utils2.c \
		  env_lst_utils1.c \
		  env_lst_utils2.c \
		  ft_utils.c

OBJETS = $(SOURCES:.c=.o)
INCLUDES = minishell.h


#### DIRECTORY ####

DIR_SRC = sources
DIR_OBJ = .object
DIR_INC = include


#### COMPLETE_PATH ####

SRC := $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJ := $(addprefix $(DIR_OBJ)/,$(OBJETS))
INC := $(addprefix $(DIR_INC)/,$(INCLUDES))


#### OTHER ####

CC := gcc
CFLAGS := -Wall -Werror -Wextra -fsanitize=address -g3
LDFLAGS := -L /usr/include -lreadline -L $(shell brew --prefix readline)/lib
CPPFLAGS := -I/Users/apercebo/homebrew/opt/readline/include
NAME := minishell


#### STANDARD_RULE ####

all : $(NAME)
re : fclean all
clean :
	rm -rf $(DIR_OBJ)
fclean : clean
	rm -rf minishell


### CUSTOM_RULE ####

$(NAME) : $(OBJ) | $(DIR_BIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(NAME) -lreadline
$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c $(INC) Makefile | $(DIR_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I $(DIR_INC)
$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)


#### UTILS #####

.PHONY : all bonus re clean fclean
