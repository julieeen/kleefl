./kleefl_init (clean)
	+ build dir structure
	+ build run_klee & run_afl init files
	- clean to remove

./kleefl_build (run on make root)
	+ make with wllvm
	+ make with afl-gcc --> OR DO IT WITH afl-clang (faster fuzzing!!)
	 	$ CC=/path/to/afl/afl-gcc ./configure
		$ make clean all
		$ For C++ programs, you'd would also want to set CXX=/path/to/afl/afl-g++.

./kleefl_pick application_name
	+ copy application from build dir to fuzz & klee roots

./kleefl_run_klee
	+ start klee -> klee.sh

./kleefl_prepare_fuzzing
	+ sort crashing, non-crashing
	+ sort same args -> group inputs
	+ create dictonary

./kleefl_run_afl
	+ start afl based on run_afl.sh file
	+ run grouped instances 
		- same args, non-crashing
		- same args, crashing
		- dictonary (-x opetion)
	+ fill up for multicore stuff