#!/usr/bin/env python




#klee --ignore-solver-failures --only-output-states-covering-new --libc=uclibc --posix-runtime ./app.bc --sym-args 0 5 10 A --sym-files 1 64 > output   

# --ignore-solver-failures: running further even is the solver crashes
# --only-output-states-covering-new: minimize file output
# --libc=uclibc --posix-runtime: support --sym-args to interface the application & external lib calls