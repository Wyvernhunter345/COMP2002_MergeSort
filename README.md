# COMP2002 - Assignment 2 

* Authors: Lucas Owers, Oscar Robertson, Jaiden Spencer
* Group name: Group 26

## Overview

This program implements a thread-safe Parallel Mergesort algorithm. It also allows the user to specify how many levels deep the recursion should go.

## Manifest

- `Makefile`: `make` build rules
- `mergesort.c`: Contains all program logic
- `mergesort.h`: Function definitions for `mergesort.c`
- `test-mergesort.c`: Program that tests the functionality of the logic in `mergesort.c`

## Building the project

You will need installed:
- `make`
- `gcc`

Inside of WSL or Linux, run `make all` to build the executable, and `make clean` to clean up any build files.

## Features and usage

This program randomly generates an array of user-defined length, and sorts it recursively using Parallel Mergesort. Users can specify a recursion level for threads allowing them to observe the program's speed the more levels are added.

At this stage it is not possible to manually specify an array of numbers.

## Testing

Testing is done through the `test-mergesort` executable.

To run the tests, execute the following command in your terminal:

```bash
./test-mergesort <input-size> <cutoff-level> <seed>
```

- Input Size: How many numbers the program should sort
- Cutoff Level: How many layers deep thread recursion should go
- Seed: The seed used for the RNG of the array


## Known Bugs

There are no known bugs at the time of submission.

## Reflection and Self Assessment

TBD.

Discuss the issues you encountered during development and testing. What
problems did you have? What did you have to research and learn on your own?
What kinds of errors did you get? How did you fix them?

What parts of the project did you find challenging? Is there anything that
finally "clicked" for you in the process of working on this project? How well
did the development and testing process go for you?

## Sources Used

- Code in `merge()` and `my_mergesort()` adapted from the [GeeksforGeeks implementation](https://www.geeksforgeeks.org/c/c-program-for-merge-sort/)

All other code was written by hand.
