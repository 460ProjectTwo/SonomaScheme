# SonomaScheme

A minimal Scheme to C++ source translator.


Usage
-----

To build the project, run
```
make
```

Then you can run the project from the current directory:
```
./P3.out foo.ss
```
This will generate several output files, including `foo.cpp`.

To compile and run an executable from the generated C++ code:
```
c++ -g -std=c++11 -c Object.cpp
c++ -g -std=c++11 -c foo.cpp
c++ -g -o foo Object.o foo.o
./foo
```


Testing
-------

Running the test suite requires [Kyua][] and [ATF][] to be installed.

[Kyua]: https://github.com/jmmv/kyua
[ATF]: https://github.com/jmmv/atf

Kyua is a testing framework for infrastructure software. It supports running
test case written with the ATF libraries.

ATF is an Automated Testing Framework. It consists of C/C++/sh libraries for
writing test programs.

On the SSU blue server, Kyua and ATF are made available through a publicly
accessible prefix. This is automatically configured by the `_test-env` script
when running tests through the Makefile.

To run the tests and display a summary of the results:
```
make test
```


Advanced Testing
----------------

First, source the `_test-env` script in your shell. This adds the project root
directory to the PATH environment variable, and on blue it adds the prefix for
Kyua and ATF to the PATH as well.
```
. ./_test-env
```

To list the available tests:
```
kyua list
```

To run all the test suites for the project:
```
kyua test
```

To view a detailed report of the last test results:
```
kyua report --verbose
```

To run a particular test suite:
```
kyua test tests/CodeGen
```

To debug a particular test case:
```
kyua debug tests/CodeGen/test:P2_1
```
