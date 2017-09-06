## KleeFL - Seeding Fuzzers With Symbolic Execution


### HowTo ...

#### Prepare dependencies or simply grab the provisioned vagrant box

    http://bit.ly/download_kleefl_box

#### Setup a project structure like this:

    mkdir project_xyz
    cd project_xyz
    python /vagrant/tools/kleefl_init


#### Select your source code, e.g.:

    cp -r /vagrant/example source

#### Build source using wllvm & afl-clang

    cd source
    /vagrant/tools/kleefl_build_cmake make all
    or
    /vagrant/tools/kleefl_build_make make all

#### Run klee symbolic execution, using the default setup
    
    ./klee/run_klee

#### Prepare klee's findings for afl-fuzz
    
    python /vagrant/tools/kleefl_prepare_fuzzing

#### Finally: Fuzz, fuzz, fuzz!
    
    ./fuzz/run_afl.sh

#### Analyze findings

    ./kleefl_crash_inspector fuzz/out
    (fuzz/out is the afl sync dir, report saved by default in vagrant shared dir /vagrant/crash_report/)

#### Analyze coverage & generate report

    python kleefl_cov_inspector {make, binary fuzz/sync_dir}
    zcov genhtml coverage.zcov cov_report


#### Further details can found in the [project report](https://github.com/julieeen/kleefl/blob/master/ResearchReport.pdf) or [check out our beautiful USENIX poster](https://github.com/julieeen/kleefl/blob/master/USENIX2017poster.pdf)
