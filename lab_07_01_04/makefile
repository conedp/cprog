CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -I inc -I inc/check
LFLAGS :=

OUT_DIR := $(shell mkdir -p ./out)

app.exe : ./out/main.o ./out/darray_ioa.o ./out/darray_op.o
	$(CC) -o $@ $^ -lm $(LFLAGS)

./out/main.o : ./src/main.c ./inc/errors.h ./inc/darray_ioa.h ./inc/darray_op.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/darray_ioa.o : ./src/darray_ioa.c ./inc/errors.h ./inc/darray_ioa.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/darray_op.o : ./src/darray_op.c ./inc/errors.h ./inc/darray_op.h ./inc/darray_ioa.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : unit debug func clean asan msan ubsan valgr

debug : CFLAGS += -g -O0
debug : app.exe ./out/main.o ./out/darray_ioa.o ./out/darray_op.o

unit_tests.exe : ./out/check_main.o ./out/check_da_alloc.o ./out/check_swap_uni.o ./out/check_cmp_uni_int.o ./out/check_mysort.o ./out/check_key.o ./out/darray_ioa.o ./out/darray_op.o
	$(CC) -o $@ $^  -Wl,--start-group -lm -lcheck -Wl,--end-group $(LFLAGS)

./out/check_main.o : ./src/check/check_main.c ./inc/errors.h ./inc/darray_ioa.h ./inc/darray_op.h ./inc/check/check_da_alloc.h ./inc/check/check_swap_uni.h ./inc/check/check_cmp_uni_int.h ./inc/check/check_mysort.h ./inc/check/check_key.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_da_alloc.o : ./src/check/check_da_alloc.c ./inc/errors.h ./inc/darray_ioa.h ./inc/check/check_da_alloc.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_swap_uni.o : ./src/check/check_swap_uni.c ./inc/errors.h ./inc/check/check_swap_uni.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_cmp_uni_int.o : ./src/check/check_cmp_uni_int.c ./inc/errors.h ./inc/darray_op.h ./inc/check/check_cmp_uni_int.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_mysort.o : ./src/check/check_mysort.c ./inc/errors.h ./inc/darray_op.h ./inc/check/check_mysort.h
	$(CC) $(CFLAGS) -c -o $@ $<

./out/check_key.o : ./src/check/check_key.c ./inc/errors.h ./inc/darray_op.h ./inc/check/check_key.h
	$(CC) $(CFLAGS) -c -o $@ $<

unit : unit_tests.exe
	./unit_tests.exe

func : app.exe
	./func_tests/scripts/func_tests.sh -v

clean :
	$(RM) -r ./out
	$(RM) app.exe unit_tests.exe ./measure/measure_app.exe

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

coverage : CFLAGS += --coverage
coverage : LFLAGS += --coverage
coverage : app.exe ./out/main.o ./out/darray_ioa.o ./out/darray_op.o
	./func_tests/scripts/func_tests.sh>/dev/null
	gcov -t -o ./out out/darray.c > ./out/darray.c.gcov
	gcov -t -o ./out out/main.c > ./out/main.c.gcov

valgr : debug
	./func_tests/scripts/func_tests.sh -mem

./out/measure_main.o : ./measure/measure_main.c ./inc/errors.h ./inc/darray_op.h
	$(CC) $(CFLAGS) -c -o $@ $<

./measure/measure_app.exe : ./out/measure_main.o ./out/darray_op.o ./out/darray_ioa.o
	$(CC) -o $@ $^  -Wl,--start-group -lm -lcheck -Wl,--end-group $(LFLAGS)

measure : CFLAGS = -std=gnu99 -Wall -Werror -Wextra -Wpedantic -I inc -I inc/check -O0
measure : LFLAGS += -lrt
measure : ./measure/measure_app.exe
	./measure/measure_app.exe 10500 > ./out/measure_data.txt
	python3 ./measure/preproc.py
	python3 ./measure/make_plot.py

