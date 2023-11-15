NAME=schedules

CC=g++
FLAGS= -std=c++11 -pedantic -Wall -Wextra -Werror

FILES=objs/uc.o objs/session.o objs/student.o objs/ui.o objs/main.o objs/manager.o objs/bst.o \
	objs/ui_s_std.o objs/ui_s_uc.o objs/ui_s_sess.o objs/ui_s_req.o objs/manager_alter.o \
	objs/ui_s_chg.o

all: $(NAME)

objs/%.o: src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(FILES)
	$(CC) $(FLAGS) $(FILES) -o $(NAME)

doxygen:
	@doxygen Doxyfile

clean:
ifeq ($(OS),Windows_NT)
	cmd /C rmdir /s /q objs
	cmd /C mkdir objs 
else
	rm -fr $(FILES)
endif

fclean: clean
ifeq ($(OS),Windows_NT)
	cmd /C del $(NAME).exe
else
	rm -fr $(NAME)
endif

re: fclean all

.PHONY: all clean fclean re
