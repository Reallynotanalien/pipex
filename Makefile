# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 20:32:19 by kafortin          #+#    #+#              #
#    Updated: 2023/02/13 16:54:33 by kafortin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = pipex

NAME_BONUS = pipex_bonus

FILES = pipex.c \
		utils.c \

FILES_BONUS = 	pipex_bonus.c \
				utils_bonus.c \

OBJS = $(FILES:.c=.o)

OBJS_BONUS = $(FILES_BONUS:.c=.o)

RM = @rm -f

.SILENT: $(OBJS) $(OBJS_BONUS)

all: $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C ./Libft
		@echo "Compiling pipex..."
		@$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)
		@echo "Completed! 🤠"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
		@$(MAKE) -C ./Libft
		@echo "Compiling pipex_bonus..."
		@$(CC) $(CFLAGS) $(OBJS_BONUS) ./Libft/libft.a -o $(NAME_BONUS)
		@echo "Completed! 🤠"

clean:
		@$(MAKE) clean -C ./Libft
		$(RM) $(OBJS) $(OBJS_BONUS)
		
fclean: 
		@$(MAKE) fclean -C ./Libft
		$(RM) $(OBJS)
		$(RM) $(OBJS_BONUS)
		$(RM) $(NAME)
		$(RM) $(NAME_BONUS)

re: fclean all

add:
	git add $(FILES)
	git add *.h
	git add Makefile

commit:
	git commit -m "$m"

push:
	git push origin master
	git push github main

git: add commit push

.PHONY: all clean fclean re add commit push git