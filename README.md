# Simple Order Book


This project implements a simple order book simulator in C++ to mimic the behavior of an exchange. It supports adding orders, canceling orders, and matching buy and sell orders based on price and time priority.


## Files

- **orderbook.h**: Contains the core `Order` and `Orderbook` classes.
- **main.cpp**: Runs the simulation and processes test files.
- **maketests.cpp**: Generates simple test cases (optional).
- **test/**: Folder containing sample test files.

## Building and Running

To compile the project, use a compiler which supports C++20. For example:

```bash
g++ -std=c++20 main.cpp -o main
```
After building, run the executable and choose a test case to run. The file **maketests.cpp** was used to generate three test cases, each with easily predictable outcomes. 
In the future, it would be interesting to create more robust test cases.