/*
 * Problem URL : https://codeforces.com/problemset/problem/2082/D
 * Submit Date : 2025-08-22
 */

#include <iostream>
using namespace std;
const int maxn = 2e5 + 10;
int n, a[maxn];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int cnt = 0, st = 0, ed = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 2; i <= n; i++) {
      if (a[i] < a[i - 1]) {
        if (!st)
          st = i;
        ed = i;
        cnt++;
      }
    }
    if (cnt == 0)
      puts("0");
    else if (cnt & 1)
      printf("%d\n", (cnt + 1) / 2);
    else if (a[ed] - a[st - 1] + 1 >= ed - st + 2)
      printf("%d\n", cnt / 2);
    else
      printf("%d\n", cnt / 2 + 1);
  }
  return 0;
}