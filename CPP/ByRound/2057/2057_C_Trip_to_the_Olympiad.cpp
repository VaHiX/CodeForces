/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/C
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, l, r;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &l, &r);
    int k = 31 - __builtin_clz(l ^ r);
    int a = l | (1 << k) - 1;
    printf("%d %d %d\n", a, a + 1, a == l ? r : l);
  }
  return 0;
}
