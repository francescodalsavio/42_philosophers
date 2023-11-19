# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frdal-sa <frdal-sa@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 14:26:29 by frdal-sa          #+#    #+#              #
#    Updated: 2023/11/18 18:50:25 by frdal-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
GDB = gdb
VAL = valgrind --leak-check=full --track-origin=yes

NAME = philosophers.a
SRCS =  ./main.c \
		./srcs/init_data.c \
		./srcs/actions.c \
		./srcs/routine.c \
		./srcs/utils.c \
		
OBJSDIR = objects
OBJS = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

all: $(NAME) philosophers

$(NAME): $(OBJS)
	@echo "Creating objects directory..."
	ar -rcs $(NAME) $(OBJS)
	@echo "Objects created!"
	
$(OBJSDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

philosophers: $(PHILO_OBJ) $(NAME)
	@echo "Creating executable..."
	$(CC) $(CFLAGS) $(PHILO_OBJ) $(NAME) -o philosophers
	@echo "Executable created!"

clean:
	@echo "Removing objects..."
	$(RM) $(OBJSDIR)
	@echo "Objects removed!"

fclean: clean
	@echo "Removing executable..."
	$(RM) philosophers philosophers.a
	@echo "Executable removed!"

re: fclean all
	@echo "Recompiled successfully!"

.SILENT: