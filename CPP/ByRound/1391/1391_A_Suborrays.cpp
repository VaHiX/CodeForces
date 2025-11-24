// Problem: CF 1391 A - Suborrays
// https://codeforces.com/contest/1391/problem/A

/*
Code Purpose:
This code generates a "good" permutation for a given integer n. A permutation is considered good if for every subarray, the bitwise OR of all elements in that subarray is greater than or equal to the length of the subarray. The solution leverages the fact that the simplest permutation, i.e., [1, 2, ..., n], satisfies this condition due to the nature of OR operations and the ordering of numbers.

Algorithm:
The approach is straightforward: for each test case, we simply output the permutation [1, 2, ..., n]. This works because:
- When we perform OR operations on numbers in increasing order, the result only increases or stays the same.
- For any subarray of length k, if we take the OR of all elements, we get at least k since each new element contributes to the OR in a way that maintains the required condition.

Time Complexity: O(n) per test case, where n is the size of the permutation. We iterate from 1 to n once to print the numbers.
Space Complexity: O(1) additional space, excluding the input/output buffer. No extra space is used beyond the variables.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 1; p <= n; p++) {
      printf("%ld ", p);  // Print numbers from 1 to n in order
    }
    puts("");  // Print a newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/