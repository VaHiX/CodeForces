// Problem: CF 1406 A - Subset Mex
// https://codeforces.com/contest/1406/problem/A

#include <cstdio>
#include <vector>
// Problem: Given a set of integers, split into two subsets A and B to maximize mex(A) + mex(B).
// Algorithm: Count occurrences of each number, then greedily assign numbers to minimize the impact on mex.
// Time Complexity: O(N) per test case, where N is the size of input array (up to 100)
// Space Complexity: O(1) since we use a fixed-size vector of size 107
int main() {
  const long N = 107;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> b(N, 0); // Count array to store frequency of each number
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++b[x]; // Increment count of number x
    }
    bool empty(true);
    long s(0);
    for (long p = 0; p < N; p++) {
      if (b[p] > 1) {
        continue; // Skip numbers that appear more than once (can be split between A and B)
      } else if (b[p] == 1 && empty) {
        s = p; // First unique number becomes part of subset A's mex
        empty = false;
      } else if (b[p] == 0) {
        // First missing number contributes to mex(A) + mex(B)
        s += (empty ? 2 : 1) * p;
        break;
      }
    }
    printf("%ld\n", s);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/