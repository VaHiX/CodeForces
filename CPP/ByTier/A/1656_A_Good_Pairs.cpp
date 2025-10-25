// Problem: CF 1656 A - Good Pairs
// https://codeforces.com/contest/1656/problem/A

/*
Algorithm: Good Pairs
Purpose: Find a pair of indices (i, j) such that for all k, the equality |a_i - a_k| + |a_k - a_j| = |a_i - a_j| holds.
Techniques: 
    - Linear scan to find minimum and maximum elements in array
    - The key insight is that a good pair (i, j) corresponds to indices of min and max elements

Time Complexity: O(n) per test case
Space Complexity: O(1)

The mathematical property used here is:
For any three numbers a, b, c, the equation |a - c| + |c - b| = |a - b| holds if and only if c lies between a and b (in terms of value).
So, choosing i as index of minimum element and j as index of maximum element guarantees that for all k, 
the middle element a_k will lie between a_i and a_j in value.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7), mx(-1e9 - 7), idxmn(0), idxmx(0); // Initialize min/max values and their indices
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > mx) {         // Update maximum and its index
        mx = x;
        idxmx = p + 1;
      }
      if (x < mn) {         // Update minimum and its index
        mn = x;
        idxmn = p + 1;
      }
    }
    printf("%ld %ld\n", idxmn, idxmx); // Output indices of min and max elements
  }
}


// https://github.com/VaHiX/codeForces/