## KleeFL - Seeding Fuzzers With Symbolic Execution


### HowTo ...

#### Prepare dependencies or simply grab the provisioned vagrant box

    http://bit.ly/download_kleefl_box

#### Setup a project structure like this:

    mkdir project_xyz
    cd project_xyz
    python /vagrant/tools/kleefl_init -- sets up two directories called 'klee' and 'fuzz' in your root project directory

#### Select your source code, e.g.:

    cp -r /vagrant/example source

#### Build source using wllvm & afl-clang

    cd source
    /vagrant/tools/kleefl_build_make make

#### Pick the target binary for KLEE
    
    Copy the binary recently built in the klee_build directory into the root project folder.
    Run the following script: 
    /vagrant/tools/klee_picker <binary>

#### Generate the test cases for AFL (KLEE symbolic execution)
    
    The previous script will add a file called app.bc within the klee directory.
    Change into the klee folder and run:
    ./run_klee.sh

#### Prepare klee's findings for afl-fuzz
    
    python /vagrant/tools/kleefl_prepare_afl

#### Finally: Fuzz, fuzz, fuzz!
    
    ../fuzz/run_afl.sh

#### Analyze findings

    ./kleefl_crash_inspector fuzz/out
    (fuzz/out is the afl sync dir, report saved by default in vagrant shared dir /vagrant/crash_report/)

#### Analyze coverage & generate report

    python kleefl_cov_inspector {make, binary fuzz/sync_dir}
    zcov genhtml coverage.zcov cov_report


#### Further details can found in the [project report](https://github.com/julieeen/kleefl/blob/master/ResearchReport.pdf) or [check out our beautiful USENIX poster](https://github.com/julieeen/kleefl/blob/master/USENIX2017poster.pdf)
