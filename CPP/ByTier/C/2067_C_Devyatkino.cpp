/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/C
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;

int _;

int main() {
  scanf("%d", &_);
  for (; _--;) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= 9; i++) {
      int k = n - i, mi = 7;
      for (; k > 0; mi = min(mi, (17 - k % 10) % 10), k /= 10)
        ;
      if (mi <= i) {
        printf("%d\n", i);
        break;
      }
    }
  }
}