NAME=schedules

CC=g++
FLAGS= -std=c++11 -pedantic -Wall -Wextra -Werror

FILES= src/student.o src/uc.o src/ui.o src/main.o

all: $(NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $*.cpp -o $*.o

$(NAME): $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

clean:
	rm -fr $(FILES)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re