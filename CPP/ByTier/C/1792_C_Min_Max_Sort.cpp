// Problem: CF 1792 C - Min Max Sort
// https://codeforces.com/contest/1792/problem/C

/*
C. Min Max Sort
Algorithm: Greedy with two pointers
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

The problem involves sorting a permutation using a specific operation:
- Choose two elements x and y
- Remove them and insert min(x,y) at the front and max(x,y) at the back
- The goal is to determine the minimum number of such operations to sort the array

Approach:
1. For each element, store its position in the input.
2. Use two pointers (left and right) starting from the middle to expand outward.
3. At each step, check if we can perform an operation that brings elements closer to their correct positions.
4. Count how many operations are needed by calculating the number of elements not yet in sorted order.

This greedy approach works because we always want to move elements as close as possible to their final sorted indices.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> pos(n + 1); // Store position of each element
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      pos[x] = p; // Position of element x is p
    }
    long left((n + 1) / 2), right((n + 2) / 2); // Start from middle
    // Expand pointers while conditions hold
    while (left > 0 && (left == right || (pos[left] < pos[left + 1] &&
                                          pos[right - 1] < pos[right]))) {
      --left;
      ++right;
    }
    // Result is total elements minus those already in correct range
    printf("%ld\n", (n - (right - left - 1)) / 2);
  }
}


// https://github.com/VaHiX/codeForces/