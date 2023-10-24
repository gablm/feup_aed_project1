NAME=schedules

CC=g++
FLAGS= -std=c++11 -pedantic -Wall -Wextra -Werror

FILES=src/uc.o src/session.o src/student.o src/ui.o src/main.o src/manager.o src/bst.o

all: $(NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $*.cpp -o $*.o

$(NAME): $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(NAME)
	doxygen docs/Doxyfile

clean:
	rm -fr $(FILES)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re