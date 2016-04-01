example: example.c
		mkdir klee_build
		mkdir afl_build
		mkdir cov_build

		clang -emit-llvm -g -c example.c -o klee_build/example.bc

		afl-gcc -o afl_build/example  example.c

		gcc -g -fprofile-arcs -ftest-coverage -o example example.c 
		mv example cov_build/
		mv example.gcno cov_build/

clean:
	rm -r klee_build
	rm -r afl_build
	rm -r cov_build