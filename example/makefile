example: example.c
		gcc -g -o example example.c
		mkdir klee-build
		mkdir afl-build
		clang -emit-llvm -g -c example.c -o klee-build/example.bc
		afl-gcc -o afl-build/example  example.c



clean:
	rm example
	rm -r klee-build
	rm -r afl-build
