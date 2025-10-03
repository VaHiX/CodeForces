/*
 * Problem URL : https://codeforces.com/contest/1423/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n, a[N][N], ans[N];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    ans[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    int pos = -1;
    for (int j = 0; j < n; j++) {
      if (ans[j] == -1) {
        if (pos == -1) {
          pos = j;
        }
        continue;
      }
      if (a[j][i] < a[pos][i]) {
        pos = j;
      }
    }
    if (ans[pos] != -1) {
      printf("-1\n");
      return 0;
    }
    ans[pos] = i;
    for (int j = 0; j < n; j++) {
      if (ans[j] == -1) {
        continue;
      }
      if (a[pos][j] < a[pos][ans[j]]) {
        ans[j] = i;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%d\n", ans[i] + 1);
  }
  return 0;
}
