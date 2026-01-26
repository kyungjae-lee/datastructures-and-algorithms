# Datastructures and Algorithms

## Development Environment
* Editor: Visual Studio Code (Version: 1.108.2 (user setup))
* Compiler: GCC (Version 15.1.0)
* Coding Standard: [Barr-C](https://barrgroup.com/sites/default/files/barr_c_coding_standard_2018.pdf)
* Commenting Style: [Doxygen](https://www.doxygen.nl/) 

## Unit Test
* Framework: Unity (Version: 2.6.1)
* To run the unit test of the module, go to the root directory of the module (e.g., `datastructures-and-algorithms/slist`), and run the following commands:
  ```shell
  $ gcc -I. -I../third_party/unity/src/ <module>.c ../third_party/unity/src/unity.c test/* -o run_<module>_test
  $ ./run_<module>_test
  ```
