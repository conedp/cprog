CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -I inc -I inc/check
LFLAGS :=
UNIT_LFLAGS := -lcheck


OUT_DIR := $(shell mkdir -p ./out)

app.exe : ./out/main.o ./out/list.o ./out/node.o
	$(CC) -o $@ $^ -lm $(LFLAGS)

./out/main.o : ./src/main.c ./inc/errors.h ./inc/list.h ./inc/node.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/list.o : ./src/list.c ./inc/errors.h ./inc/node.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/node.o : ./src/node.c ./inc/errors.h ./inc/node.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : unit unit_home debug func clean asan msan ubsan valgr

debug : CFLAGS += -g -O0
debug : app.exe ./out/main.o ./out/list.o ./out/node.o

unit_tests.exe : ./out/check_main.o ./out/check_concatenate.o ./out/check_helpers.o ./out/check_delete_excess_spaces.o ./out/check_find_substring.o ./out/list.o ./out/node.o
	$(CC) -o $@ $^  -Wl,--start-group -lm $(UNIT_LFLAGS) -Wl,--end-group $(LFLAGS)

# -lcheck -lrt -lsubunit

./out/check_main.o : ./src/check/check_main.c ./inc/errors.h ./inc/list.h ./inc/node.h ./inc/check/check_concatenate.h ./inc/check/check_helpers.h ./inc/check/check_delete_excess_spaces.h ./inc/check/check_find_substring.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_concatenate.o : ./src/check/check_concatenate.c ./inc/errors.h ./inc/check/check_concatenate.h ./inc/list.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_delete_excess_spaces.o : ./src/check/check_delete_excess_spaces.c ./inc/errors.h ./inc/list.h ./inc/check/check_delete_excess_spaces.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_helpers.o : ./src/check/check_helpers.c ./inc/errors.h ./inc/list.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_find_substring.o : ./src/check/check_find_substring.c ./inc/errors.h ./inc/list.h ./inc/check/check_find_substring.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<


unit : unit_tests.exe
	./unit_tests.exe

unit_home : UNIT_LFLAGS += -lrt -lsubunit
unit_home : unit_tests.exe
	./unit_tests.exe

func : app.exe
	./func_tests/scripts/func_tests.sh -v

clean :
	$(RM) -r ./out
	$(RM) app.exe unit_tests.exe

msan : CC := clang
msan : CFLAGS += -fsanitize=leak -fno-omit-frame-pointer -fPIE
msan : LFLAGS += -fsanitize=leak -pie -fno-omit-frame-pointer
msan : debug
	./func_tests/scripts/func_tests.sh -v

asan : CC := clang
asan : CFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan : LFLAGS += -fsanitize=address -fno-omit-frame-pointer
asan : debug
	./func_tests/scripts/func_tests.sh -v

ubsan : CC := clang
ubsan : CFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
ubsan : LFLAGS += -fsanitize=undefined -fno-omit-frame-pointer
ubsan : debug
	./func_tests/scripts/func_tests.sh -v

valgr : debug
	./func_tests/scripts/func_tests.sh -mem

