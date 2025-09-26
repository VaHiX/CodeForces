/*
 * Problem URL : https://codeforces.com/problemset/problem/273/A
 * Submit Date : 2025-08-19
 */

#include <bits/stdc++.h>
#define FOR(i, a) for (int i = 0; i < (a); i++)
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  long long stair[n];
  FOR(i, n) { scanf("%lld", &stair[i]); }
  int x;
  scanf("%d", &x);
  while (x--) {
    int w, h;
    scanf("%d %d", &w, &h);
    if (stair[w - 1] > stair[0]) {
      printf("%lld\n", stair[w - 1]);
      stair[0] = stair[w - 1] + h;
    } else {
      printf("%lld\n", stair[0]);
      stair[0] += h;
    }
  }
}
