CC=clang
CFLAGS+=-O3
DFSAN_FLAGS=-DDF_ANALYSIS

%.o: %.c
	$(CC) -g -c -fpic -o $@ $< $(CFLAGS) $(DFSAN_FLAGS)

text: textinstrumentation.o bitcode
	$(CC) -shared -o libinstrumentation.so $<

null: nullinstrumentation.o bitcode
	$(CC) -shared -o libinstrumentation.so $<

binary: binaryinstrumentation.o dinamite_time.o
	make bitcode
	$(CC) -shared -o libinstrumentation.so $^

hotarea: hotareainstrumentation.o
	clang $(DFSAN_FLAGS) -emit-llvm hotareainstrumentation.c -c -g -o instrumentation.bc
	$(CC) -shared -o libinstrumentation.so $^

bitcode: textinstrumentation.c
	clang -emit-llvm $< -c -g -o instrumentation.bc

clean:
	rm *.o instrumentation.bc

