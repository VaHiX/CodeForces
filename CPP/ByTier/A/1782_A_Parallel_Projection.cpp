/*
 * Problem URL : https://codeforces.com/problemset/problem/1782/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int t, w, d, h, a, b, f, g;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d%d%d%d", &w, &d, &h, &a, &b, &f, &g);
    printf("%d\n",
           h + min(a + f + abs(b - g),
                   min(b + g + abs(a - f), min(w - a + w - f + abs(b - g),
                                               d - b + d - g + abs(a - f)))));
  }
  return 0;
}