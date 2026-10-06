# DSA Assignment 2 - Question 10

**Logistics Company – Sorting Packages by Weight**

**Subject:** PCCST303 – Data Structures and Algorithms
**College:** Vimal Jyothi Engineering College

## Problem Statement

A logistics company receives package weights:
`20, 15, 20, 10, 15, 20, 25, 10`

Each package has a unique Package ID.

### Tasks
- **(a)** Implement **Merge Sort** and **Quick Sort** to sort packages by weight. Record important intermediate steps.
- **(b)** Modify so that packages of equal weight retain original relative order. Verify using Package IDs.
- **(c)** Analyse with respect to:
  - Duplicate values
  - Stability
  - Number of comparisons
  - Time complexity
  - Space complexity

Determine which algorithm is more suitable when original order of equal-weight packages must be preserved.

## Files in this Repository

| File              | Description                                      |
|-------------------|--------------------------------------------------|
| `package_sort.c`  | Complete C program (Merge Sort + Quick Sort)     |
| `input_data.txt`  | Input package weights and assigned IDs           |
| `output.txt`      | Sample execution output with intermediate steps  |
| `ANALYSIS.txt`    | Detailed complexity analysis & conclusion        |
| `README.md`       | This file                                        |

## How to Run

```bash
gcc -o package_sort package_sort.c
./package_sort
```

The program prints:
- Intermediate steps of both algorithms
- Final sorted sequences
- Stability verification for equal weights
- Comparison counts

## Key Results

**Merge Sort (Stable):**
`(P4,10) (P8,10) (P2,15) (P5,15) (P1,20) (P3,20) (P6,20) (P7,25)`

**Quick Sort (Unstable):**
`(P8,10) (P4,10) (P5,15) (P2,15) (P1,20) (P3,20) (P6,20) (P7,25)`

**Conclusion:**
Merge Sort is preferred when stability (preserving original order of equal-weight packages) is required.

## Author
Student submission for DSA Assignment 2 – Question 10
