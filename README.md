# EE538 Lab 1 - Matrix Multiplication (Divide & Conquer and Strassen)

## Author

- Name: thutapea
- Student ID: 4688737874
- Email: spotifytimh@gmail.com

## Program Summary

`4688737874lab1.cpp` multiplies two n x n integer matrices with two recursive
methods and reports the running time of each.

1. Reads `input.txt`. The first line is the matrix size n, the next n lines are
   matrix A, and the last n lines are matrix B.
2. Since both recursive methods need to split a matrix into four equal halves,
   the matrices are padded with rows and columns of zeros up to the next power
   of two (for example a 3x3 input is stored as 4x4). The zero padding does not
   change the product, so the answer is read back from the top-left n x n part
   of the result.
3. Question 1 - `divideAndConquer()` splits A and B into four n/2 x n/2 blocks
   and computes the four blocks of C with 8 recursive multiplications and 4
   additions:
   C11 = A11\*B11 + A12\*B21, C12 = A11\*B12 + A12\*B22,
   C21 = A21\*B11 + A22\*B21, C22 = A21\*B12 + A22\*B22.
   The recursion stops at a 1x1 matrix, where the product is a single
   multiplication.
4. Question 2 - `strassen()` splits the matrices the same way but computes the
   seven products M1 ... M7 defined in the lab handout, then combines them into
   C11 = M1 + M4 - M5 + M7, C12 = M3 + M5, C21 = M2 + M4 and
   C22 = M1 - M2 + M3 + M6. It also recurses down to 1x1 matrices.
5. Question 3 - each method is timed with `clock()` from `<ctime>`; the running
   time is the end value minus the start value, written out as an integer
   number of clock ticks.

All matrices are allocated with double pointers (`int **`) as required; no
`std::vector` and no matrix library is used. Only `<fstream>` and `<ctime>` from
the standard library are included.

### Complexity (Question 3)

- Naive method: three nested loops, O(n^3).
- Divide and conquer: T(n) = 8T(n/2) + O(n^2), which by the Master Theorem is
  O(n^3), the same as the naive method.
- Strassen: T(n) = 7T(n/2) + O(n^2) = O(n^(log2 7)) = O(n^2.8074).

Strassen does fewer multiplications, so it is usually faster than the plain
divide and conquer version in the measured times. Both allocate temporary
submatrices in every recursive call, so their measured running times are worse
than a naive triple loop would be even though the asymptotic bounds say
otherwise.

## Output Files

- `output_m1.txt` - product from the divide and conquer method.
- `output_m2.txt` - product from Strassen's method.
- `output_q3.txt` - the two integer running times (divide and conquer first,
  then Strassen) separated by a space.

In `output_m1.txt` and `output_m2.txt` each number is followed by a space and
each row is on its own line, matching the example output given with the lab.

## Instructions

Put `input.txt` in the same directory as the executable, then:

```
g++ -std=c++17 4688737874lab1.cpp -o lab1
./lab1
```

Running the program creates `output_m1.txt`, `output_m2.txt` and
`output_q3.txt` in the working directory.

## Notes

- `input.txt` in this directory is the 3x3 example from the lab handout, kept
  for testing. `input_7_.txt` is the same example under its original name.
- Corner cases such as a 1x1 matrix work: the padded size is 1 and both
  functions return immediately from the base case.
- There are no known non-working parts.

## References

- Lab 1 handout (EE538) for the input/output format, the divide and conquer
  block equations, and the definitions of M1 ... M7 and C11 ... C22 used in
  `strassen()`.
- Cormen, Leiserson, Rivest, Stein, *Introduction to Algorithms*, chapter on
  matrix multiplication, for the recurrences T(n) = 8T(n/2) + O(n^2) and
  T(n) = 7T(n/2) + O(n^2) quoted above.

All code was written by me; no code was copied from any website.
