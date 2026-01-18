CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic
LFLAGS :=
UNIT_LFLAGS := -lcheck

OUT_DIR := $(shell mkdir -p ./out)


unit : unit_tests.exe
	./unit_tests.exe

unit_home : UNIT_LFLAGS += -lrt -lsubunit
unit_home : unit_tests.exe
	./unit_tests.exe

./out/associative_array_impl_2.o : ./associative_array_impl_2.c ./associative_array.h ./list.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/list.o : ./list.c ./list.h
	$(CC) $(CFLAGS) -c -o $@ $<

unit_tests.exe : ./out/check_main.o ./out/check_assoc_array_each.o ./out/check_assoc_array_find.o ./out/check_assoc_array_min.o ./out/check_assoc_array_clear.o ./out/check_assoc_array_max.o ./out/check_assoc_array_remove.o ./out/check_assoc_array_insert.o ./out/associative_array_impl_2.o ./out/list.o
	$(CC) -o $@ $^  -Wl,--start-group -lm $(UNIT_LFLAGS) -Wl,--end-group $(LFLAGS)

./out/check_main.o : check_main.c ./check_assoc_array_each.h ./check_assoc_array_find.h ./check_assoc_array_min.h ./check_assoc_array_clear.h ./check_assoc_array_max.h ./check_assoc_array_remove.h ./check_assoc_array_insert.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_each.o : ./check_assoc_array_each.c ./check_assoc_array_each.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_find.o : ./check_assoc_array_find.c ./check_assoc_array_find.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_min.o : ./check_assoc_array_min.c ./check_assoc_array_min.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_clear.o : ./check_assoc_array_clear.c ./check_assoc_array_clear.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_max.o : ./check_assoc_array_max.c ./check_assoc_array_max.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_remove.o : ./check_assoc_array_remove.c check_assoc_array_remove.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_assoc_array_insert.o : ./check_assoc_array_insert.c ./check_assoc_array_insert.h ./associative_array.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean unit unit_home

clean :
	$(RM) -r out/
	$(RM) unit_tests.exe
