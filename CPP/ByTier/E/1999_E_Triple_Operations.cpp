// Problem: CF 1999 E - Triple Operations
// https://codeforces.com/contest/1999/problem/E

/*
E. Triple Operations
Algorithm: Preprocessing using dynamic programming to compute prefix sums of operations needed for numbers from 1 to n.
Time Complexity: O(2e5) preprocessing + O(1) per query => overall O(N + T)
Space Complexity: O(2e5) for the vector v

The problem asks for minimum operations to reduce all integers in range [l, r] to 0,
using a specific operation: pick x and y, replace them with 3x and floor(y/3).
Each number's "cost" is defined as how many times we need to apply this operation to get 0.
We precompute for all numbers up to 2e5 and use prefix sums for range queries.

Key idea:
- For number i, v[i] = 1 + v[i/3], base case v[0] = 0
- The number of operations needed to reduce i to 0 is equal to how many times we can divide it by 3, plus one operation each step.
- We use a prefix sum array to quickly calculate total operations in any interval [l, r]
*/

#include <cstdio>
#include <vector>
int main() {
  std::vector<long> v(2e5 + 7);
  // Build the vector: v[p] = 1 + v[p / 3], representing steps to reach 0 from p
  for (long p = 1; p < v.size(); p++) {
    v[p] = 1 + v[p / 3];
  }
  // Compute prefix sums of the operations count
  for (long p = 1; p < v.size(); p++) {
    v[p] += v[p - 1];
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    // Calculate result using inclusion-exclusion with prefix sums
    long res = v[b] - 2 * v[a - 1] + v[a];
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/