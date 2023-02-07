# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kafortin <kafortin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 20:32:19 by kafortin          #+#    #+#              #
#    Updated: 2023/01/27 17:17:43 by kafortin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = pipex

FILES = pipex.c \
		utils.c \

OBJS = $(FILES:.c=.o)

RM = @rm -f

.SILENT: $(OBJS)

all: $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C ./Libft
		@echo "Compiling pipex..."
		@$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)
		@echo "Completed! 🤠"

clean:
		@$(MAKE) clean -C ./Libft
		$(RM) $(OBJS)
		
fclean: 
		@$(MAKE) fclean -C ./Libft
		$(RM) $(OBJS)
		$(RM) $(NAME)

re: fclean all

add:
	git add $(FILES)
	git add *.h
	git add Makefile

commit:
	git commit -m "$m"

push:
	git push origin master

git: add commit push

.PHONY: all clean fclean re add commit push git