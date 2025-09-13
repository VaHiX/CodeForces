/*
 * Problem URL : https://codeforces.com/problemset/problem/1835/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int pw[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};
int t, a, b, c;
ll n;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%lld", &a, &b, &c, &n);
    for (int i = pw[a - 1]; i < pw[a]; i++) {
      int l = max(pw[b - 1], pw[c - 1] - i), r = min(pw[b], pw[c] - i);
      if (r - l < n) {
        n -= max(r - l, 0);
        continue;
      }
      printf("%d + %lld = %lld\n", i, l + n - 1, i + l + n - 1), n = 0;
      break;
    }
    if (n)
      puts("-1");
  }
  return 0;
}