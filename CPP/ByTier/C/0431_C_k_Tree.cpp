/*
 * Problem URL : https://codeforces.com/problemset/problem/431/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>
int n, k, D, d[2][110], M = 1e9 + 7, S, N;
main() {
  for (scanf("%d%d%d", &n, &k, &D), d[0][0] = 1, S = 1; S <= n; S++)
    for (N = 1; N <= k && N <= S;)
      (d[0][S] += d[0][S - N]) %= M, (d[1][S] += d[N < D][S - N++]) %= M;
  printf("%d", d[1][n]);
}