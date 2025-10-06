# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 20:54:21 by alebarbo          #+#    #+#              #
#    Updated: 2025/10/06 15:47:56 by alebarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                 COLOR CODES                                  #
#==============================================================================#
RED   = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

#==============================================================================#
#                                  VARIABLES                                   #
#==============================================================================#

# Names
NAME         = minishell
PROJECT_NAME = MINISHELL

# Paths
SRC_PATH   = srcs
INC_PATH   = incs
BUILD_PATH = .build

# Source files
SRC = $(addprefix $(SRC_PATH)/, \
		ft_minishell.c \
		ft_get_ps1.c \
		ft_read_line.c \
		ft_signal_handler.c \
)

# Object files
OBJ = $(addprefix $(BUILD_PATH)/, $(notdir $(SRC:.c=.o)))

# LIBFT
LIBFT_PATH     = libft
LIBFT_INC_PATH = $(LIBFT_PATH)/includes
LIBFT_LINK     = ft
LIBFT_NAME     = $(LIBFT_PATH)/lib$(LIBFT_LINK).a

# Compiler and Flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -ggdb -fsanitize=address
INC     = -I$(INC_PATH) -I$(LIBFT_INC_PATH)
LDFLAGS = -L$(LIBFT_PATH) -l$(LIBFT_LINK) -lreadline

# Utility Commands
RM      = rm -f
MKDIR_P = mkdir -p
RMDIR   = $(RM) -r
MAKE    = make --no-print-directory

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LDFLAGS) -o $@
	@echo "$(GREEN)[$(PROJECT_NAME)] Executable compiled: $(NAME).$(RESET)"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c | $(BUILD_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)
	@echo "$(GREEN)[$(PROJECT_NAME)] Build directory created.$(RESET)"

$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH) all

clean:
	@$(RMDIR) $(BUILD_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@echo "$(RED)[$(PROJECT_NAME)] Clean: Cleaned object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(RED)[$(PROJECT_NAME)] Full Clean: executable $(NAME) removed.$(RESET)"

re: fclean all