// Problem: CF 2124 G - Maximise Sum
// https://codeforces.com/contest/2124/problem/G

/*
G. Maximise Sum
Algorithm: Dynamic Programming with Segment and Prefix Minimums
Time Complexity: O(n^2) amortized per test case due to nested loops and optimizations.
Space Complexity: O(n) for auxiliary arrays.

This problem involves finding the maximum sum of prefix minimums over all operations that cost at least x,
where each operation merges two elements a[i] and a[j] (i < j) with cost j - i.
The goal is to compute for each x from 0 to n-1, the maximum sum of prefix minimums under the constraint that the operation's cost is at least x.

Approach:
1. Preprocess increasing and decreasing stack indices for efficient segment operations.
2. Compute prefix sums of minimum values.
3. Use sliding window technique with two pointers to evaluate valid operations.
4. For each valid merge operation, update result array with the computed sum.
5. Finally propagate maximum values backwards to satisfy all cost thresholds.

*/

#include <stdio.h>
#include <string.h>
#define N 1000000
#define INF 0x3f3f3f3f
int min(int a, int b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    static int aa[N], bb[N], ii[N], jj[N];
    static long long ss[N], ans[N];
    int n, m, k, g, h, i, i_, j, l, r, a, d;
    long long s;
    scanf("%d", &n);
    memset(jj, -1, n * sizeof *jj);
    for (i = 0; i < n; i++)
      scanf("%d", &aa[i]);
    m = 0;
    for (i = 0; i < n; i++)
      if (m == 0 || aa[ii[m - 1]] > aa[i])
        ii[m++] = i;
    k = 0;
    for (j = n - 1; j >= 0; j--)
      if (k == 0 || aa[jj[k - 1]] < aa[j])
        jj[k++] = j;
    a = n + 1;
    for (i = 0; i + 1 < n; i++) {
      a = min(a, aa[i]);
      ss[i + 1] = ss[i] + a;
    }
    memset(ans, 0, n * sizeof *ans);
    for (h = 0; h < m; h++) {
      i = ii[h], i_ = h + 1 == m ? n : ii[h + 1];
      bb[i] = h == 0 ? INF : aa[ii[h - 1]];
      for (j = i + 1; j < i_; j++)
        bb[j] = min(bb[j - 1], aa[j]);
      s = 0;
      for (g = 0, l = i_, r = i_; g < k && jj[g] > i; g++) {
        j = jj[g];
        a = aa[i] + aa[j];
        while (r > j)
          s -= bb[--r];
        while (l > i && (l > r || bb[l - 1] <= a))
          s += bb[--l];
        ans[j - i] = max(ans[j - i], ss[i] + (long long)(l - i) * a + s +
                                         (j < i_ ? 0 : ss[j] - ss[i_]));
        if (l == i)
          break;
      }
    }
    for (d = n - 2; d >= 0; d--)
      ans[d] = max(ans[d], ans[d + 1]);
    for (d = 0; d < n; d++)
      printf("%lld ", ans[d]);
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/