# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 13:35:48 by ghambrec          #+#    #+#              #
#    Updated: 2025/02/11 13:00:47 by ghambrec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------- MAIN ---------- #
NAME = so_long
CC = cc
INCLUDE_DIR = ./include
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

# ---------- LIB ---------- #
LIB_DIR = ./lib
LIBFT_DIR = $(LIB_DIR)/myLibft
LIBFT_NAME = libft.a
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT_NAME)
MLX_DIR = $(LIB_DIR)/MLX42
MLX_NAME = $(MLX_DIR)/build/libmlx42.a
MLX_FULL = $(MLX_NAME) -ldl -lglfw -pthread -lm

# ---------- SOURCES ---------- #
VPATH = ./sources ./sources/map_validation
SOURCES =	main.c error_handling.c textures.c player.c helper.c map.c \
			map_validation.c validate_characters.c validate_rectangular.c validate_surrounding.c validate_path.c

# ---------- OBJECTS ---------- #
OBJECT_DIR = objects
OBJECTS = $(addprefix $(OBJECT_DIR)/, $(SOURCES:.c=.o))

# ---------- COLORS AND STUFF ---------- #
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m

# ---------- RULES ---------- #
all: $(NAME)

$(NAME): checkMyLibft checkMLX $(LIBFT_NAME) createLibMLX $(OBJECTS)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT_FULL) $(MLX_FULL) -o $(NAME)
	@if [ -f $(NAME) ]; then \
		echo "$(CYAN)--------------------------------------$(NC)"; \
		echo "$(GREEN)BUILD PROCESS COMPLETED SUCCESSFULLY!$(NC)"; \
		echo "$(CYAN)--------------------------------------$(NC)"; \
	else \
		echo "$(RED)failed to compile $(NAME)$(NC)"; \
		exit 1; \
	fi

checkMyLibft:
	@if [ -d $(LIBFT_DIR) ]; then \
		echo "$(GREEN)myLibft already exists$(NC)"; \
	else \
		echo "$(YELLOW)Downloading myLibft...$(NC)"; \
		mkdir -p $(LIB_DIR); \
		curl -L -o $(LIBFT_DIR).zip https://github.com/ghambrec/42-myLibft/archive/refs/heads/master.zip > /dev/null 2>&1; \
		unzip -o $(LIBFT_DIR).zip > /dev/null 2>&1; \
		mv 42-myLibft-master $(LIBFT_DIR); \
		rm $(LIBFT_DIR).zip; \
		if [ -d $(LIBFT_DIR) ]; then \
			echo "$(GREEN)myLibft downloaded$(NC)"; \
		else \
			echo "$(RED)Error downloading myLibft$(NC)"; \
			exit 1; \
		fi \
	fi	

checkMLX:
	@if [ -d $(MLX_DIR) ]; then \
		echo "$(GREEN)MLX42 already exists$(NC)"; \
	else \
		echo "$(YELLOW)Downloading MLX42...$(NC)"; \
		mkdir -p $(LIB_DIR); \
		curl -L -o $(MLX_DIR).zip https://github.com/codam-coding-college/MLX42/archive/refs/heads/master.zip > /dev/null 2>&1; \
		unzip -o $(MLX_DIR).zip > /dev/null 2>&1; \
		mv MLX42-master $(MLX_DIR); \
		rm $(MLX_DIR).zip; \
		if [ -d $(LIBFT_DIR) ]; then \
			echo "$(GREEN)MLX downloaded$(NC)"; \
		else \
			echo "$(RED)Error downloading MLX$(NC)"; \
			exit 1; \
		fi \
	fi	

$(LIBFT_NAME):
	@echo "$(YELLOW)Creating $(LIBFT_NAME)...$(NC)"
	@make -C $(LIBFT_DIR) > $(LIBFT_DIR)/make_log.txt
	@if [ -f $(LIBFT_DIR)/$(LIBFT_NAME) ]; then \
		echo "$(GREEN)$(LIBFT_NAME) successfully created$(NC)"; \
	else \
		echo "$(RED)failed to compile $(LIBFT_DIR)$(NC)"; \
		exit 1; \
	fi

createLibMLX:
	@echo "$(YELLOW)Creating MLX42-LIB...$(NC)"
	@mkdir -p $(MLX_DIR)/make_log
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build > $(MLX_DIR)/make_log/cmake_log.txt
	@make -C $(MLX_DIR)/build -j4 > $(MLX_DIR)/make_log/make_log.txt
	@if [ -f $(MLX_NAME) ]; then \
		echo "$(GREEN)MLX42-LIB successfully created$(NC)"; \
	else \
		echo "$(RED)Error creating MLX42-LIB$(NC)"; \
		exit 1; \
	fi

$(OBJECT_DIR)/%.o: %.c | $(OBJECT_DIR)
	@printf "$(YELLOW)Compiling $(CYAN)$<\n$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECT_DIR):
	@echo "$(YELLOW)Creating $(OBJECT_DIR) directory$(NC)"
	@mkdir -p $(OBJECT_DIR)

clean:
	@echo "$(RED)Cleaning object files$(NC)"
	@rm -rf $(OBJECT_DIR)

fclean: clean
	@echo "$(RED)Removing $(NAME)$(NC)"
	@rm -f $(NAME)
	@rm -f $(NAME_CHECKER)
	@if [ -d $(LIBFT_DIR) ]; then \
		make fclean -C $(LIBFT_DIR); \
	fi

re: fclean all

# test rule - compile without flags
test: CFLAGS = -I $(INCLUDE_DIR)
test: $(NAME)

del: fclean
	@echo "$(RED)Removing LIB folder$(NC)"
	@rm -rf $(LIB_DIR)

.PHONY: all clean fclean re test del