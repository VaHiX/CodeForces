/*
 * Problem URL : https://codeforces.com/contest/1097/problem/B
 * Submit Date : 2025-08-29
 */

#import <ios>
int i, j, k, n, p[16][360];
main() {
  p[0][0] = 1;
  for (scanf("%d", &n); i++ < n;)
    for (j = !scanf("%d", &k); j < 360; j++)
      p[i][(j + k) % 360] += p[i - 1][j],
          p[i][(j - k + 360) % 360] += p[i - 1][j];
  puts(p[n][0] ? "YES" : "NO");
}
