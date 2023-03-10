# The Monty Hall Problem

The _Monty Hall_ problem or _Three Door_ problem -where a person chooses one of
three doors in hope of winning a valuable prize but is subsequently offered the
choice of changing his or her selection- is a well known and often discussed
probability problem. Monty Hall was the legendary host of a television game show
_Let's Make a Deal_, which debuted on network television.

As depicted previously, the key element to the game show involved three doors.
Behind each door there was a prize. Two of the prizes were of no value, while
the third door held a prize of significant value. The participant was asked to
choose a door. After the selection of a door, Monty Hall would reveal one of the
"no value" prizes behind a door. Since the host knew the location of the "high
value" prize, he would never open this opportunity to stay with his original
choice or to change to the remaining un-opened door.

The purpose of this app is to perform a simulation of the game with a random
generator. Then, run thousands or millions of games to estimate the chance to
win the prize either staying or switching the door.

## Project structure and dependencies

This project is developed using the C++11 standard, CMake as build system and
documented with Doxygen. The framework utilized for unit and integration 
testing is `gtest`. In the following snippet, the top-level directory layout is 
depicted:

```
.
├── build                   # Compiled files
├── docs                    # Documentation source files
├── src                     # Source files 
├── test                    # unit and integration tests 
├── inc                     # Header files
└── README.md               # Repository description
```

## Dependencies

In this project the following dependencies were implemented:

* [`argparse`](https://github.com/p-ranav/argparse)
* [`gtest`](https://github.com/google/googletest)
* [`spdlog`](https://github.com/gabime/spdlog)

# Development tools

In order to start working with this repository, the following tools need to be
installed:

* [`cmake`](https://cmake.org/)
* [`GCC`](https://gcc.gnu.org/)
* [`pre-commit`](https://pre-commit.com/)
* [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)
* [`cppcheck`](https://cppcheck.sourceforge.io/)
* [`libstdc++-dev`](https://libcxx.llvm.org/)

TL;DR:

Run the following command

```
sudo apt install cmake build-essentials pre-commit python3-pip clang-format cppcheck libstdc++-dev
pip install pre-commit
```

# Compile and run

As stated earlier, this project is `CMake` based, in order to be built g++
must be installed as well as CMake >= 3.16.

In order to build this project run:

```
cd build 
cmake .. 
make -j<n_cores>
```

in order to use `monty_hall_simulator`, here's some help:

```
Usage: monty_hall_simulation [--help] [--version] [-s VAR] [-j VAR] [-v] [-f VAR]

This software implements a simulation of the Monty Hall problem, it will run the amount of simulations specified by the -s flag

Optional arguments:
  -h, --help    shows help message and exits 
  -v, --version prints version information and exits 
  -s            The number of simulations to run [default: 1000]
  -j            The number of jobs to run simultaneously [default: 1]
  -v            Set logging to debug level for verbosity 
  -f            Set path of logfile [default: ""]
```

To run unit and integration tests:

```
cd build
ctest
```

# Features

* Standard logging system to `stdout` with info, warning and debug levels (debug
  level is enabled with `-v` flag).
* All logging can be sent to a file using the `-f <path_to_file_arg>`
* Several simulations can be processed with simultaneous jobs using the `-j
  <n_cores>` flag
* the number of configurations can be set by the user with the flag `-j
  <int_value>`

# TODO

* encapsulate threads function into its own class to make it more readable
