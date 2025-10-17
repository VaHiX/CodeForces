/*
 * Problem URL : https://codeforces.com/contest/2025/problem/C
 * Submit Date : 2025-09-10
 */

#import <regex>
int n, k, r, i, j, p;
main() {
  for (scanf("%*d"); ~scanf("%d%d", &n, &k); r = i = j = p = 0) {
    int a[n];
    while (i < n)
      scanf("%d", a + i++);
    for (std::sort(a, a + n); j<n; r = ++j - i> r ? j - i : r) {
      i = a[j] > p ? j : i;
      while (a[j] - a[i] >= k)
        i++;
      p = a[j] + 1;
    }
    printf("%d ", r);
  }
}