/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/G
 * Submit Date : 2025-08-14
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
