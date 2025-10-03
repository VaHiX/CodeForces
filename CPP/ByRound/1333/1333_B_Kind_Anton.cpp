/*
 * Problem URL : https://codeforces.com/problemset/problem/1333/B
 * Submit Date : 2025-08-16
 */

#include <stdio.h>
int t, n, a[100000], b[100000];
bool solve() {
  bool c[3]{};
  for (int i = 0; i < n; i++) {
    if (a[i] > b[i]) {
      if (!c[0])
        return 0;
    } else if (a[i] < b[i]) {
      if (!c[2])
        return 0;
    }
    c[a[i] + 1] = 1;
  }
  return 1;
}
int main() {
  scanf("%d", &t);
  for (; t--;) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", a + i);
    }
    for (int i = 0; i < n; ++i) {
      scanf("%d", b + i);
    }
    if (solve()) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
}