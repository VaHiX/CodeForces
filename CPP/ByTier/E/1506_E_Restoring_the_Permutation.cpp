/*
 * Problem URL : https://codeforces.com/problemset/problem/1506/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
int n, top, a[N], st[N];
bool b[N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), b[i] = 0;
    int p = 1;
    for (int i = 1; i <= n; i++)
      if (a[i] != a[i - 1])
        b[a[i]] = 1, printf("%d ", a[i]);
      else {
        while (b[p])
          ++p;
        b[p] = 1, printf("%d ", p);
      }
    puts("");
    top = 0;
    for (int i = 1; i <= n; i++)
      if (a[i] != a[i - 1]) {
        printf("%d ", a[i]);
        for (int j = a[i - 1] + 1; j < a[i]; j++)
          st[++top] = j;
      } else
        printf("%d ", st[top--]);
    puts("");
  }
}