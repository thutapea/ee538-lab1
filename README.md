# EE538 Lab 1 

## Author

 thutapea
 4688737874
 thutapea@usc.edu

## Program Summary

This implements 2 matrix mults

1. Reads input.txt
2. divideAndConquer() splits A and B 
   and computes the four blocks of C with 8 recursive multiplications and 4
   additions given by the provided formula
3. strassen() computes the other formula provided and only uses 7
4. Lastly they are timed in q3

### Complexity (Question 3)

- Naive method:  O(n^3).
- Divide and conquer: T(n) = 8T(n/2) + O(n^2) the same as the naive method.
- Strassen: T(n) = 7T(n/2) + O(n^2) = O(n^(log2 7)) = O(n^2.8074).

Strassen does fewer multiplications, so it is  faster. Both allocate 
aux memory in recursion, so their worse
than a naive method due to overhead.

## Output Files

- `output_m1.txt` - divide and conquer
- `output_m2.txt` - Strassen's
- `output_q3.txt` - time



## Instructions

Run
```
g++ -std=c++17 4688737874lab1.cpp -o lab1
./lab1
```

