/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 3;
int T, n, x[N], knd, inp, inp2, a, b, cnt[N];
inline void qry(int x, int y) { printf("? %d %d\n", x, y), fflush(stdout); }
int main() {
  scanf("%d", &T);
  while (T--) {
    knd = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      cnt[i] = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &x[i]);
    for (int i = 1; i <= n; i++) {
      if (cnt[x[i]])
        knd = 1;
      cnt[x[i]] = 1;
    }
    if (knd) {
      for (int i = 1; i <= n; i++)
        if (!cnt[i])
          knd = i;
      qry(knd, 1 + (knd == 1));
      scanf("%d", &inp);
      if (inp)
        printf("! B\n");
      else
        printf("! A\n");
    } else {
      for (int i = 1; i <= n; i++) {
        if (x[i] == 1)
          a = i;
        if (x[i] == n)
          b = i;
      }
      qry(a, b), scanf("%d", &inp);
      qry(b, a), scanf("%d", &inp2);
      if (inp >= n - 1 && inp == inp2)
        printf("! B\n");
      else
        printf("! A\n");
    }
    fflush(stdout);
  }
  return 0;
}
