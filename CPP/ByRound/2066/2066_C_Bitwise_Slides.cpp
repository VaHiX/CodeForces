// Problem: CF 2066 C - Bitwise Slides
// https://codeforces.com/contest/2066/problem/C

/* 
C. Bitwise Slides
Algorithms/Techniques: Dynamic Programming with Bitmasking and Coordinate Compression
Time Complexity: O(n log n) per test case due to sorting and coordinate compression
Space Complexity: O(n) for arrays and auxiliary structures

The problem involves processing an array where each element can be XORed with three variables P, Q, R in any order.
We must count how many valid sequences of operations result in P, Q, R being pairwise equal after every step.
This is solved using dynamic programming on a compressed coordinate space to optimize transitions.
*/
#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;
const int N = 2e5 + 5;
const ll P = 1e9 + 7;
int T, n, a[N], c[N], d[N];
ll ans, f[N];

void solve() {
  ans = 0, f[0] = 1; // Initialize answer and DP array
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] ^= a[i - 1], c[i] = a[i]; // Compute prefix XORs and store in c
  }
  sort(c + 1, c + 1 + n); // Sort prefix XORs to enable coordinate compression
  int m = unique(c + 1, c + 1 + n) - c - 1; // Remove duplicates from c and get size m
  for (int i = 1; i <= n; i++)
    d[i] = lower_bound(c, c + m + 1, a[i]) - c; // Map each prefix XOR to compressed index
  for (int i = 1; i <= n; i++)
    f[d[i - 1]] = (3 * f[d[i - 1]] + 2 * f[d[i]]) % P; // Transition based on recurrence relation
  for (int i = 0; i <= n; i++)
    ans = (ans + f[d[i]]) % P, f[d[i]] = 0; // Sum up all valid paths and reset DP array
  printf("%lld\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/