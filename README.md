Kleefl 
======
### Seeding fuzzers with symbolic execution

---

## Example of usage:

### Grab the vagrant box

    https://owncloud.sec.t-labs.tu-berlin.de/owncloud/public.php?service=files&t=2c28a437ebb75a33ee127dd4ea827726

### Setup a project structure

    mkdir project_xyz
    cd project_xyz
    /vagrant/tools/kleefl_init


### Select your source code, e.g.:

    cp -r /vagrant/example source

### Build the source with wllvm & afl-clang

    cd source
    /vagrant/tools/kleefl_build make

    (in case of exmaple proj, just do "make")

### Run Klee symbolic execution
    
    ./klee/run_klee		// using default setup (feel free to change)

### Prepare Klee findings for afl-fuzz
    
    /vagrant/tools/kleefl_prepare_fuzzing
    (in project root dir)

### Finally: Fuzz!
    
    ./fuzz/run_afl.sh

### Analyze findings

    ./kleefl_crash_inspector fuzz/out
    (fuzz/out is afl sync dir, report saved by default in vagrant shared dir /vagrant/crash_report/)

### Analyze coverage

    kleefl_cov_inspector {make, binary fuzz/sync_dir}
    & generate webreport by:
    zcov genhtml coverage.zcov cov_report


### Report
    
    Further details can found in the project report.
