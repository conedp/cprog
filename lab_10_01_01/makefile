CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -I inc -I inc/check
LFLAGS :=
UNIT_LFLAGS := -lcheck


OUT_DIR := $(shell mkdir -p ./out)

app.exe : ./out/main.o ./out/data_io.o ./out/data_struct.o ./out/list.o ./out/node.o ./out/list_io.o
	$(CC) -o $@ $^ -lm $(LFLAGS)

./out/main.o : ./src/main.c ./inc/errors.h ./inc/data_io.h ./inc/data_struct.h ./inc/list.h ./inc/node.h ./inc/list_io.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/data_io.o : ./src/data_io.c ./inc/errors.h ./inc/data_io.h ./inc/data_struct.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/data_struct.o : ./src/data_struct.c ./inc/errors.h ./inc/data_struct.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/list_io.o : ./src/list_io.c ./inc/errors.h ./inc/list_io.h ./inc/node.h ./inc/data_io.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/list.o : ./src/list.c ./inc/errors.h ./inc/list.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/node.o : ./src/node.c ./inc/errors.h ./inc/node.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : unit unit_home debug func clean asan msan ubsan valgr

debug : CFLAGS += -g -O0
debug : app.exe ./out/main.o ./out/data_io.o ./out/data_struct.o ./out/list.o ./out/node.o ./out/list_io.o

unit_tests.exe : ./out/check_main.o ./out/check_find.o ./out/check_helpers.o ./out/check_insert.o ./out/check_remove_duplicates.o ./out/check_sort.o ./out/check_sorted_insert.o ./out/list.o ./out/node.o ./out/data_struct.o ./out/list_io.o
	$(CC) -o $@ $^  -Wl,--start-group -lm $(UNIT_LFLAGS) -Wl,--end-group $(LFLAGS)

# -lcheck -lrt -lsubunit

./out/check_main.o : ./src/check/check_main.c ./inc/errors.h ./inc/list.h ./inc/node.h ./inc/check/check_find.h ./inc/check/check_helpers.h ./inc/check/check_insert.h ./inc/check/check_remove_duplicates.h ./inc/check/check_sorted_insert.h ./inc/check/check_sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_find.o : ./src/check/check_find.c ./inc/errors.h ./inc/list.h ./inc/check/check_find.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_helpers.o : ./src/check/check_helpers.c ./inc/errors.h ./inc/check/check_helpers.h ./inc/list.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_insert.o : ./src/check/check_insert.c ./inc/errors.h ./inc/list.h ./inc/check/check_insert.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_remove_duplicates.o : ./src/check/check_remove_duplicates.c ./inc/errors.h ./inc/list.h ./inc/check/check_remove_duplicates.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_sort.o : ./src/check/check_sort.c ./inc/errors.h ./inc/list.h ./inc/check/check_sort.h ./inc/check/check_helpers.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_sorted_insert.o : ./src/check/check_sorted_insert.c ./inc/errors.h ./inc/list.h ./inc/check/check_sorted_insert.h ./inc/check/check_helpers.h
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

