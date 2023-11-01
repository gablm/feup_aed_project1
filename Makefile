NAME=schedules

CC=g++
FLAGS= -std=c++11 -pedantic -Wall -Wextra -Werror

FILES=objs/uc.o objs/session.o objs/student.o objs/ui.o objs/main.o objs/manager.o objs/bst.o \
	objs/ui_s_std.o objs/ui_s_uc.o objs/ui_s_sess.o objs/ui_s_req.o objs/manager_alter.o

all: $(NAME)

objs/%.o: src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

doxygen:
	doxygen docs/Doxyfile

clean:
	rm -fr $(FILES)

fclean: clean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re