kleefl 
======
### Seeding fuzzers with symbolic execution

---

## Example of usage:

### Prepare dependencies or grab the vagrant box

    https://owncloud.sec.t-labs.tu-berlin.de/owncloud/public.php?service=files&t=2c28a437ebb75a33ee127dd4ea827726

### Setup project structure

    mkdir project_xyz
    cd project_xyz
    python /vagrant/tools/kleefl_init


### Select your source code, e.g.:

    cp -r /vagrant/example source

### Build source using wllvm & afl-clang

    cd source
    python /vagrant/tools/kleefl_build make

### Run klee symbolic execution, using our default setup
    
    ./klee/run_klee

### Prepare klee's findings for afl-fuzz
    
    python /vagrant/tools/kleefl_prepare_fuzzing

### Finally: Fuzz!
    
    ./fuzz/run_afl.sh

### Analyze findings

    ./kleefl_crash_inspector fuzz/out
    (fuzz/out is the afl sync dir, report saved by default in vagrant shared dir /vagrant/crash_report/)

### Analyze coverage

    python kleefl_cov_inspector {make, binary fuzz/sync_dir}
    // and generate a report using ...
    zcov genhtml coverage.zcov cov_report


### Further details can found in the project report
