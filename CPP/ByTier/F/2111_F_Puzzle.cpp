/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/F
 * Submit Date : 2025-08-17
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
inline void solve() {
  int p, s;
  cin >> p >> s;
  int d = __gcd(p, s);
  p /= d;
  s /= d;
  for (int i = s; i <= 50000; i += s) {
    int j = i / s * p;
    if (j % 2 || i < j / 2 - 1)
      continue;
    j /= 2;
    if (1LL * (j / 2) * (j - j / 2) >= i) {
      printf("%d\n", i);
      int x = j / 2, y = j - j / 2;
      for (int k = 1; k <= x; k++) {
        i--;
        printf("%d %d\n", k, 1);
      }
      for (int k = 2; k <= y; k++) {
        i--;
        printf("%d %d\n", 1, k);
      }
      for (int k = 2; k <= x; k++) {
        for (int l = 2; l <= y; l++) {
          if (i) {
            i--;
            printf("%d %d\n", k, l);
          }
        }
      }
      return;
    }
  }
  printf("-1\n");
}
int main() {
  int TTTQ;
  cin >> TTTQ;
  while (TTTQ--) {
    solve();
  }

  return 0;
}