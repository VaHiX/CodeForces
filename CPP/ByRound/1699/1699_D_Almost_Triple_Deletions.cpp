// Problem: CF 1699 D - Almost Triple Deletions
// https://codeforces.com/contest/1699/problem/D

/*
Algorithm: Dynamic Programming with Prefix Analysis
Time Complexity: O(n^2)
Space Complexity: O(n)

This solution uses dynamic programming to find the maximum number of equal elements
that can remain after performing valid deletion operations. The key idea is to track
the maximum number of equal elements that can be formed ending at each position,
considering the constraints that we can only delete adjacent elements with different values.

The dp state f[i] represents the maximum number of equal elements achievable
for the prefix of length i.

For each prefix, we compute the maximum number of equal elements that can be left
by considering all possible previous positions where a deletion could have occurred.

The variable k tracks the maximum frequency of any element in the current prefix being considered.
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 5e3 + 7;
int T_T, i, j, n, k, a[N], f[N], c[N];
int main() {
  for (scanf("%d", &T_T); T_T--;) {
    for (scanf("%d", &n), i = 1; i <= n; ++i)
      scanf("%d", a + i);
    for (i = 1; i <= n + 1; ++i) {
      for (f[i] = -N, k = j = 0; j < i; ++j)
        c[a[j]] = 0;
      for (j = i - 1; j != -1; --j) {
        if ((i - j & 1) && k * 2 < i - j && (a[j] == a[i] || i > n || !j))
          f[i] = max(f[i], f[j] + 1);
        k = max(k, ++c[a[j]]);
      }
    }
    printf("%d\n", f[n + 1] - 1);
  }
}


// https://github.com/VaHiX/CodeForces/