# Graph

Graph class with several graph algorithms including depth-first search, 
breadth-first search, dijkstra's shortest path, minimum spanning tree

[Author: Bill Zhao](https://www.iambillzhao.com/)

## Included Files

- `CMakeLists.txt`: For the use of `make` to compile.

- `graph.h, graph.cpp`: Graph class

- `graphtest.cpp`: Test functions

- `main.cpp`: A generic main file to call testAll() to run all tests

- `output.txt`: Output from `./simple.compile.sh > output.txt 2>&1`
showing how the program is compiled and run

- `simplecompile.sh`: Unix bash script file to compile, run clang-tidy
  as well as other programs and then delete the executable. Can be
  used to create an output.txt file

- `.clang-tidy`: Specify the options for clang-tidy program, so we do
  not have to enter them on the command line each time.
  Usage: `clang-tidy *.cpp -- -std=c++14`

- `.clang-format`: LLVM specification of how formatting should work.
  
- `.gitattributes`: Options for git.

- `.gitignore`: Files that should not be checked into git.

- `.travis.yml`: Trigger Travis CI to compile and run the program.

## Compile and Run
```
./simplecompile.sh
```


## Style check
Based on options defined in `.clang-tidy`
```
clang-tidy *.cpp -- -std=c++14
```

Note: NOLINT was used in some cases (Weight/From/To) to simplify the code
in order to be used as public. One function could be created to better hide
the value if needed.

### Style Explanation
These options are defined in `.clang-tidy` file.

If you make changes to `.clang-tidy` file, explain the reasoning below

Perform all check except the following:

- cert-err58-cpp: Using static variable which may cause throw
- cppcoreguidelines-avoid-magic-numbers: magic numbers needed for testing
- cppcoreguidelines-owning-memory: not using gsl, so assigning new owners
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- cppcoreguidelines-pro-bounds-constant-array-index: array index not constant
- cppcoreguidelines-pro-bounds-pointer-arithmetic: need to use array indexes
- cppcoreguidelines-special-member-functions: no move constructor or move assignment for now
- fuchsia-*: Checks specific to fuschia system
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-global-names-in-headers: OK to say `using namespace std;` for class code
- google-readability-braces-around-statements: allow compact code without `{`
- hicpp-braces-around-statements: want compact code
- hicpp-no-array-decay: allow assert
- hicpp-special-member-functions: no move constructor or move assignment for now
- llvm-header-guard: header guards do not have full directory name
- modernize-pass-by-value: Not using move for objects
- modernize-use-trailing-return-type: not ready for auto func() -> int format yet
- readability-braces-around-statements: allow compact code without `{` (this option
9.0.0) is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using
- readability-magic-numbers: needed for testing
