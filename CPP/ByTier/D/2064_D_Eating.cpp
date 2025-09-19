/*
 * Problem URL : https://codeforces.com/problemset/problem/2064/D
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long ll;

int n, q, a[200002], s[200002], t[200002][32];

void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), s[i] = s[i - 1] ^ a[i];
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= __lg(a[i]); j++)
      t[i][j] = i;
    for (int j = __lg(a[i]) + 1; j <= 30; j++)
      t[i][j] = t[i - 1][j];
  }
  while (q--) {
    int x, to = n;
    scanf("%d", &x);
    for (int j = 30; j >= 0; j--)
      if (x >= (1 << j)) {
        int tmp = t[to][j];
        x ^= s[tmp] ^ s[to];
        to = tmp;
        if (!to || a[to] > x)
          break;
        x ^= a[to--];
      }
    printf("%d ", n - to);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
    putchar('\n');
  }
}