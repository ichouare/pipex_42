# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 10:54:47 by ichouare          #+#    #+#              #
#    Updated: 2023/01/29 16:46:23 by ichouare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAMEB = bonuspipex

CC = cc 

FLAG = -Wall -Wextra  -Werror 

HEADER = ./pipex.h

SRCSB = ./Bonus/miltipipe.c  ./Bonus/multi_utils.c ./Bonus/ft_strlen.c ./Bonus/ft_strcmp.c ./Bonus/ft_strjoin.c ./Bonus/ft_split.c  ./Bonus/ft_getnextLine.c  ./Bonus/ft_calloc.c\
./Bonus/ft_getnextLine_util.c ./Bonus/ft_calloc.c ./Bonus/ft_bzero.c \

SRCS = pipex.c  ft_strlen.c ft_strcmp.c ft_strjoin.c ft_split.c  ft_getnextLine.c \
ft_getnextLine_util.c ft_calloc.c ft_bzero.c \


OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)


all: $(NAME)

Bonus :  $(NAMEB)

$(NAME): $(OBJS) 
	$(CC)  $^ -o $@
 
$(NAMEB) :  $(OBJSB)
	$(CC) $^ -o $@
	
%.o : %.c  $(HEADER)
	$(CC) $(FLAG)  -c -o $@ $<

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME) $(NAMEB)

re: fclean all 