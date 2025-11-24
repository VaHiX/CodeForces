// Problem: CF 1256 B - Minimize the Permutation
// https://codeforces.com/contest/1256/problem/B

/*
B. Minimize the Permutation
Algorithms/Techniques: Greedy algorithm with simulation of adjacent swaps

Time Complexity: O(n^2) per test case, due to nested loops for finding minimum and shifting elements.
Space Complexity: O(n) for storing the input vector and output vector.

Problem:
You are given a permutation of length n. You can perform at most n-1 operations, each allowing you to swap adjacent elements.
Goal: Find lexicographically smallest possible permutation after performing some operations.

Approach:
The algorithm simulates building the result step by step:
1. Find the minimum element in the remaining part of array
2. Move all elements between current position and this minimum to output
3. Swap minimum with its left neighbor to move it forward
Repeat until entire array is processed.
*/
#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long start(0);
    std::vector<long> b;
    while (start < n) {
      long mn(a[start]), nxt(start); // Initialize minimum and its index
      for (long p = start; p < n; p++) {
        if (a[p] < mn) {
          mn = a[p];
          nxt = p;
        }
      }
      b.push_back(mn); // Add the smallest element found to result
      for (long p = start; p < nxt - 1; p++) {
        b.push_back(a[p]); // Move elements before minimum to output
      }
      if (nxt > start) { // If minimum is not at start
        a[nxt] = a[nxt - 1]; // Swap minimum with its left neighbor
        start = nxt; // Move pointer past the moved element
      } else {
        ++start; // Simply move to next element
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", b[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/