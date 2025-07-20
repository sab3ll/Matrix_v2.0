CC			:=	g++
CFLAGS		:=	-Wall \
				-Werror \
				-Wextra \
				-Wpedantic \
				-std=c++17
TFLAGS		:=	-lgtest \
				-lgtest_main \
				-pthread

LIB_DIR		:=	lib
SRC_DIR		:=	src
OBJ_DIR		:=	obj
TESTS_DIR	:=	tests

SRC_FILES	:=	$(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES	:=	$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
MATRIX_LIB	:=	s21_matrix_oop.a

.PHONY: all clean clang cppcheck test

all: $(MATRIX_LIB)

$(MATRIX_LIB): $(OBJ_FILES)
	ar rcs $(LIB_DIR)/$(MATRIX_LIB) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clang:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 clang-format -i
	rm .clang-format

cppcheck:
	find . -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 cppcheck --std=c++17 --enable=all --force

test: $(MATRIX_LIB)
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/s21_matrix_oop_test.cpp -I $(SRC_DIR) -o $(OBJ_DIR)/s21_matrix_oop_test.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/s21_matrix_oop_test.o $(LIB_DIR)/$(MATRIX_LIB) $(TFLAGS) -o $(TESTS_DIR)/bin/s21_matrix_oop_test
	$(TESTS_DIR)/bin/s21_matrix_oop_test

clean:
	$(RM) $(OBJ_DIR)/* $(LIB_DIR)/* $(TESTS_DIR)/bin/*
	clear
