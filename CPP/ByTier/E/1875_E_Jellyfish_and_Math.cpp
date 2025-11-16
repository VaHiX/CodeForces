// Problem: CF 1875 E - Jellyfish and Math
// https://codeforces.com/contest/1875/problem/E

/*
 * Code Purpose:
 * This program solves a problem where we start with values (x, y) = (a, b) and want to reach (c, d)
 * using a set of bitwise operations. It uses a precomputed BFS to determine minimum operations.
 *
 * Algorithms:
 * - Preprocessing BFS on a state space of 30-bit values, each encoded as a 5-base number.
 * - Each bit position is treated independently and mapped to a state.
 * - BFS is used to compute minimal steps to reach any state.
 *
 * Time Complexity:
 * - Preprocessing: O(5^8) = O(390625) due to 8 bits in each base-5 number.
 * - Each query: O(30) for processing 30 bits.
 *
 * Space Complexity:
 * - O(5^8) = O(390625) for storing dp array.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;
const int S = 4e5 + 5, Inf = 0x3f3f3f3f;
int pw5[10] = {}, dp[S] = {};
queue<int> Q;

// Inline function to update minimum value
inline void checkmin(int &x, int y) {
  if (y < x)
    x = y;
}

// Helper function to extract digit at position i in base-5 representation of mask
inline int w(int mask, int i) { return (mask / pw5[i]) % 5; }

// Function to map a, b, m (bit values) to index
inline int f(int a, int b, int m) { return (a << 2) | (b << 1) | m; }

// Function to map c, d to index
inline int g(int c, int d) { return (c << 1) | d; }

// Function to compute next state after applying operation 'opt'
inline int work(int mask, int opt) {
  int ret = 0;
  for (int a = 0; a < 2; a++)
    for (int b = 0; b < 2; b++)
      for (int m = 0; m < 2; m++) {
        int x = w(mask, f(a, b, m)), c = x >> 1, d = x & 1;
        if (opt == 1)
          c = c & d;
        else if (opt == 2)
          c = c | d;
        else if (opt == 3)
          d = c ^ d;
        else
          d = m ^ d;
        ret += pw5[f(a, b, m)] * g(c, d);
      }
  return ret;
}

// Preprocessing BFS setup to compute shortest distances
inline void init() {
  pw5[0] = 1;
  for (int i = 1; i <= 8; i++)
    pw5[i] = pw5[i - 1] * 5;
  memset(dp, 0x3f, sizeof(dp));
  int mask = 0;
  for (int a = 0; a < 2; a++)
    for (int b = 0; b < 2; b++)
      for (int m = 0; m < 2; m++)
        mask += pw5[f(a, b, m)] * g(a, b);
  dp[mask] = 0, Q.push(mask);
  while (Q.size()) {
    int s = Q.front();
    Q.pop();
    for (int opt = 0; opt < 4; opt++) {
      int t = work(s, opt);
      if (dp[t] == Inf)
        dp[t] = dp[s] + 1, Q.push(t);
    }
  }
  for (int mask = 0; mask < pw5[8]; mask++)
    for (int i = 0; i < 8; i++)
      if (w(mask, i) == 4) {
        for (int x = 1; x <= 4; x++)
          checkmin(dp[mask], dp[mask - x * pw5[i]]);
        break;
      }
}

// Solve individual test case
inline void solve() {
  int A = 0, B = 0, C = 0, D = 0, M = 0, mask = pw5[8] - 1;
  scanf("%d %d %d %d %d", &A, &B, &C, &D, &M);
  for (int i = 0; i < 30; i++) {
    int a = (A >> i) & 1, b = (B >> i) & 1, c = (C >> i) & 1, d = (D >> i) & 1,
        m = (M >> i) & 1;
    if (w(mask, f(a, b, m)) == 4)
      mask -= (4 - g(c, d)) * pw5[f(a, b, m)];
    else if (w(mask, f(a, b, m)) != g(c, d)) {
      printf("-1\n");
      return;
    }
  }
  printf("%d\n", (dp[mask] < Inf) ? dp[mask] : -1);
}

int T = 0;
int main() {
  init();
  scanf("%d", &T);
  for (int i = 0; i < T; i++)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/