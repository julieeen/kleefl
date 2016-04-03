example: example.c
		mkdir klee_build
		mkdir afl_build

		clang -emit-llvm -g -c example.c -o klee_build/example.bc

		afl-gcc -o afl_build/example  example.c

		# gcc -g -fprofile-arcs -ftest-coverage -o example example.c 
	

clean:
	rm -r klee_build
	rm -r afl_build