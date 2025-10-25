/*
 * Problem URL : https://codeforces.com/contest/319/problem/B
 * Submit Date : 2025-09-06
 */

#include <iostream>
using namespace std;
const int N = 100010;
int a[N], s[N], ans, num[N], tt = 0, cnt = 0;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) {
    cnt = 0;
    while (tt && s[tt] <= a[i]) {
      cnt = max(cnt, num[s[tt]]);
      tt--;
    }
    if (tt)
      num[a[i]] = cnt + 1;
    s[++tt] = a[i];
  }
  for (int i = 1; i <= n; i++)
    ans = max(ans, num[a[i]]);
  printf("%d", ans);
}
