// Problem: CF 2044 F - Easy Demon Problem
// https://codeforces.com/contest/2044/problem/F

/*
F. Easy Demon Problem
time limit per test4 seconds
memory limit per test256 megabytes

Algorithms/Techniques: 
- Preprocessing sums and differences
- Using boolean arrays to mark possible values of sums
- Multiplication table generation using inclusion-exclusion principle
- Query processing by checking precomputed results

Time Complexity: O(n + m + N^2 + q)
Space Complexity: O(N)

For an arbitrary grid, Robot defines its beauty to be the sum of elements in the grid.
Robot gives you an array a of length n and an array b of length m. You construct a n by m grid M such that M[i][j] = a[i] * b[j].
Then, Robot gives you q queries, each consisting of a single integer x. For each query, determine whether or not it is possible to perform the following operation exactly once so that M has a beauty of x:
Choose integers r and c such that 1 <= r <= n and 1 <= c <= m
Set M[i][j] to be 0 for all ordered pairs (i,j) such that i=r, j=c, or both.

Note: queries are not persistent, meaning that you do not actually set any elements to 0 in the process — you are only required to output if it is possible to find r and c such that if the above operation is performed, the beauty of the grid will be x.
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int a[2 * N], b[2 * N], visa[2 * N], visb[2 * N], ans[2 * N];
ll suma, sumb;
int n, m, q;
ll mabs(ll a) { return max(a, -a); } // Returns absolute value of a
int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    suma += a[i];
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &b[i]);
    sumb += b[i];
  }
  // Mark all possible differences in a
  for (int i = 0; i < n; i++) {
    ll d = suma - a[i]; // Difference after removing a[i]
    if (mabs(d) < N)
      visa[d + N] = 1; // Mark in visa array shifted by N
  }
  // Mark all possible differences in b
  for (int i = 0; i < m; i++) {
    ll d = sumb - b[i]; // Difference after removing b[i]
    if (mabs(d) < N)
      visb[d + N] = 1; // Mark in visb array shifted by N
  }
  // For each pair of possible products, check if it's achievable via the operations
  for (int i = 1; i < N; i++)
    for (int j = 1; i * j < N; j++) {
      ans[N + i * j] |= visa[N + i] && visb[N + j]; // Positive i, positive j
      ans[N + i * j] |= visa[N - i] && visb[N - j]; // Negative i, negative j
      ans[N - i * j] |= visa[N + i] && visb[N - j]; // Positive i, negative j
      ans[N - i * j] |= visa[N - i] && visb[N + j]; // Negative i, positive j
    }
  while (q--) {
    int x;
    scanf("%d", &x);
    if (ans[x + N]) // Check precomputed result
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/