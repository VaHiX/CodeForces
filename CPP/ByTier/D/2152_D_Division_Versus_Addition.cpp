// Problem: CF 2152 D - Division Versus Addition
// https://codeforces.com/contest/2152/problem/D

/*
D. Division Versus Addition
Problem Description:
This problem involves computing the minimum number of moves Poby (the first player) makes in a two-player game played on a subarray.
Each element can be reduced by dividing by 2 (Poby's move) or incremented by 1 (Rekkles' move).
The goal is to find the optimal score for Poby when both players play optimally.
Time Complexity: O(n + q) per test case, where n is size of array, q is number of queries
Space Complexity: O(n) for precomputed arrays
*/

#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;
const int N = 250000;
int T, n, Q, a[N + 5], sum[N + 5], dg[N + 5], sf[N + 5];
int main() {
  scanf("%d", &T);
  while (T--) {
    cin >> n >> Q;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      sum[i] = dg[i] = sf[i] = 0;
      int x = a[i], ds = log2(x);
      if (x == pow(2, ds) + 1)
        dg[i] = 1;               // Check if x is of form 2^k + 1
      if (x == pow(2, ds))
        sf[i] = 1;               // Check if x is a power of 2
      while (x > 1) {
        sum[i]++;                // Count number of divisions needed to reach 1
        x >>= 1;                 // Right shift by one bit (equivalent to dividing by 2)
      }
      sum[i] += sum[i - 1];      // Prefix sum of total operations
      dg[i] += dg[i - 1];        // Prefix sum of "2^k + 1" elements
      sf[i] += sf[i - 1];        // Prefix sum of powers of 2
    }
    while (Q--) {
      int l, r;
      scanf("%d%d", &l, &r);
      // Formula: total steps - Rekkles moves - (Poby's extra moves) / 2
      printf("%d\n", (sum[r] - sum[l - 1]) + (r - l + 1) - (sf[r] - sf[l - 1]) -
                         (dg[r] - dg[l - 1] + 1) / 2);
    }
  }
}


// https://github.com/VaHiX/CodeForces/