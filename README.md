# Juosan Solver - Bactracking

## Overview

This project is dedicated to solving Juosan puzzles&mdash;which have been proven to be NP-complete&mdash;using the backtracking algorithm.
The backtracking algorithm implemented has an asymptotic complexity of $O(2^{mn})$, where $m \times n$ is the size of the puzzle.

For more information about the puzzle, see [https://www.nikoli.co.jp/en/puzzles/juosan](https://www.nikoli.co.jp/en/puzzles/juosan).

## Contents

This repository includes the following:

* **Juosan Solver**: The solver is implemented in C++ using the backtracking algorithm. You can find the code in the `codes/solver_backtracking.cpp` file. An additional solver using the exhaustive search method is also provided in `codes/solver_exhaustive.cpp`.
* **Juosan Solution Verifier**: The verifier checks whether a given solution to a Juosan puzzle is correct. You can find the code in the `codes/verifier.cpp` file.
* **Test Cases**: Seventy test cases of Juosan puzzles in plain text format sourced from [Janko](https://www.janko.at/Raetsel/Juosan/index.htm). You can find them in the `test_cases` directory.
* **Experimental Data**: Experimental data regarding the runtime of the backtracking solver and verifier. You can find the data in the `experimental_data/Juosan Runtime Experiment.xlsx` file.
* **preprint**: Preprint of our related paper, submitted to Jurnal Ilmu Komputer dan Informasi (JIKI), this preprint will be deleted once the paper is published and available online at https://jiki.cs.ui.ac.id/. Updated 21 July 2023: our manuscript has been accepted for publication at JIKI and will appear in volume 17 no. 1 (February 2024).

## How to use

Using the Juosan solver and verifier is straightforward. Here are the basic steps you need to follow:

1. Compile the `solver_backtracking.cpp` and `verifier.cpp` files using your preferred C++ compiler.
2. Run the resulting executable file.
3. To use the solver, input the Juosan puzzle according to the [Input/Output Format](#inputoutput-format) section.
4. To use the verifier, input the Juosan puzzle followed by the corresponding solution according to the [Input/Output Format](#inputoutput-format) section.

## Input/Output Format

The Juosan puzzle can be inputted using the following format:

```
m n
r
N_1 N_2 ... N_r
R_{1,1} R_{1,2} ... R_{1,n}
R_{2,1} R_{2,2} ... R_{2,n}
...
R_{m,1} R_{m,2} ... R_{m,n}
```

where:

* `m` and `n` are integers representing the number of rows and columns in the puzzle.
* `r` is an integer representing the number of territories.
* `N_i` is the number occurring in territory $i$. If territory $i$ does not contain a number, then `N_i` $= -1$.
* `R_{i,j}` is an integer label of the territory containing cell $(i,j)$.

The Juosan solution can be inputted using the following format:
```
S_{1,1} S_{1,2} ... S_{1,n}
S_{2,1} S_{2,2} ... S_{2,n}
...
S_{m,1} S_{m,2} ... S_{m,n}
```

where `S_{i,j}` is either the character `-` or `|` which denotes what to fill in cell $(i,j)$.

For example, the following input (for the verifier) represents the Juosan puzzle depicted in the picture below:
```
5 5
7
3 1 -1 2 3 -1 4
1 1 1 2 2
3 4 5 5 5
3 4 6 6 6
3 4 6 6 6
3 7 7 7 7
- - - - |
- | - - -
| - | | -
| | - | |
| - - - -
```

<img src="https://user-images.githubusercontent.com/54428874/236688739-8c00e9c9-1950-4c1b-aabe-5a0fc299e332.png" alt="example input" width="400">

Here is an example of the output generated by the solver for the above input (excluding the solution part). The above instance does not have a unique solution, apparently:
```
- - - - |
- | - - -
| - | | -
- | - - |
- - - - -
Time taken: 0.003 ms
```
Here is an example of the output generated by the verifier for the above input:
```
Configuration is a solution
Time taken: 2.3 microsecond(s)
```

Alternatively, the input can be fed from a text file.
For example, using `test_cases/6x6_1.in`&mdash;which follows the same format&mdash;like this:
```
[solver executable] < ../test_cases/6x6_1.in
```
