/*
 * Problem URL : https://codeforces.com/problemset/problem/1101/C
 * Submit Date : 2025-08-18
 */

#import <regex>
long long l, a[100000];
int i, j, t, n, m, g, b[100000], s[100000];
main() {
  for (scanf("%d", &t); t--;) {
    scanf("%d", &n);
    for (i = j = m = g = 0; i < n; i++) {
      scanf("%lld%d", &l, b + i);
      a[i] = l << 32 | i;
    }
    std::sort(a, a + n);
    for (; j < n; j++) {
      i = a[j];
      g += a[j] >> 32 > m;
      m = b[i] > m ? b[i] : m;
      s[i] = 2 - g % 2;
    }
    if (g < 2) {
      n = 1;
      *s = -1;
    }
    for (i = 0; i < n; i++)
      printf("%d ", s[i]);
  }
}
