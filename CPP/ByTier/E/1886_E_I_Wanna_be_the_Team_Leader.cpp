// Problem: CF 1886 E - I Wanna be the Team Leader
// https://codeforces.com/contest/1886/problem/E

/*
 * Problem: Assign programmers to projects such that each project has at least one programmer,
 * and all programmers assigned to a project have stress tolerance greater than or equal to
 * difficulty level divided by number of programmers.
 *
 * Algorithm:
 * 1. Sort programmers in descending order of stress tolerance.
 * 2. Precompute for each project, the minimum number of programmers needed to satisfy its difficulty.
 * 3. Use dynamic programming with bitmask to find a valid assignment of projects to programmers.
 * 4. Reconstruct the assignment from DP table.
 *
 * Time Complexity: O(m * n * 2^m)
 * Space Complexity: O(m * n + 2^m)
 */
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 5;
const int M = 25;
const int K = 1 << 20 | 5;
int n, m, a[N], b[M], f[K], fr[K], g[M][N], id[N], num[M];
vector<int> ans[M];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), id[i] = i;
  sort(id + 1, id + 1 + n, [&](int x, int y) { return a[x] > a[y]; });
  for (int i = 0; i < m; i++)
    scanf("%d", &b[i]);
  for (int i = 0; i < m; i++)
    for (int l = 0, r = 0; l <= n; l++) {
      // Find minimum r such that (r - l) * a[id[r]] >= b[i]
      while ((r - l) * a[id[r]] < b[i] && r <= n)
        r++;
      g[i][l] = r;
    }
  for (int i = 1; i < 1 << m; i++)
    f[i] = n + 1;
  for (int i = 0; i < 1 << m; i++)
    if (f[i] != n + 1)
      for (int j = 0; j < m; j++)
        if (!(i >> j & 1) && f[i | 1 << j] > g[j][f[i]]) {
          f[i | 1 << j] = g[j][f[i]];
          fr[i | 1 << j] = j;
        }
  if (f[(1 << m) - 1] == n + 1)
    return printf("NO\n"), 0;
  printf("YES\n");
  for (int i = (1 << m) - 1; i; i = i ^ 1 << fr[i])
    num[fr[i]] = f[i ^ 1 << fr[i]];
  for (int i = 0; i < m; i++) {
    printf("%d ", g[i][num[i]] - num[i]);
    for (int j = num[i] + 1; j <= g[i][num[i]]; j++)
      printf("%d ", id[j]);
    printf("\n");
  }
}


// https://github.com/VaHiX/CodeForces/