NAME = lem-in
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
HEADER = lem-in.h

SRC = lem-in.c libft.c # gnl.c #\
	  validate.c \
	  operations.c \
	  sort.c \
	  sort_utils.c \
	  movements.c \
	  libft.c
OBJ = $(SRC:c=o)

Color_Off	=	"\[\033[0m\]"       # Text Reset
BWhite		=	"\[\033[1;37m\]"    # White
BRed		=	"\[\033[1;31m\]"    # Red
BGreen		=	"\[\033[1;32m\]"    # Green

all: $(NAME)

$(NAME):	$(OBJ)
	@echo "\033[1;37m\\n\nStarting lem-in..."
	@$(CC) $(FLAGS) -fsanitize=address -o $(NAME) $(OBJ)
	@echo "\033[1;32mCompiling finished."
	@echo "\033[0m"


%.o: %.c
	@printf "\033[0;33mGenerating lem-in objects... %-10.10s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

.o: %.c
	@echo "\033[1;32m\\n\Creating lem-in objects..."
	@${CC} ${FLAGS} -c $< -o $@

clean:
	@echo "\033[1;32m\\nDeleting objects..."
	@rm -f $(OBJ) $(OBJB)
	@echo "\033[0m"

fclean:
	@echo "\033[1;32m\\nDeleting objects..."
	@rm -f $(OBJ) $(OBJB)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

run:
	@make re
	./lem-in < ./maps/subject1.map

errors:
	@make re 
	./lem-in < ./maps/no_ants.map
	./lem-in < ./maps/dup_ants.map
	./lem-in < ./maps/no_start.map
	./lem-in < ./maps/dup_start.map
	./lem-in < ./maps/no_end.map
	./lem-in < ./maps/dup_end.map
	./lem-in < ./maps/one_room.map

bonus: $(OBJB)
	@echo "\033[0;32m\n\nCompiling lem-in (with bonuses)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJB)
	@echo "\n\033[0mCompiling bonus finished."

.PHONY: clean fclean re bonus
