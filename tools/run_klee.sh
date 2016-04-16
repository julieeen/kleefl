#!/bin/bash
klee --max-instruction-time=30. --simplify-sym-indices --max-memory=2000 --max-sym-array-size=4096 --ignore-solver-failures --only-output-states-covering-new --libc=uclibc --posix-runtime ./app.bc --sym-args 1 3 12 --sym-files 1 128 > /dev/null


# --ignore-solver-failures: running further even is the solver crashes
# --optimize: remove dead code, optimize bytecode
# --only-output-states-covering-new: minimize file output
# --libc=uclibc --posix-runtime: support --sym-args to interface the application & external lib calls