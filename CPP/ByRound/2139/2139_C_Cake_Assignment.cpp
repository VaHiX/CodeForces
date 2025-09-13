/*
 * Problem URL : https://codeforces.com/contest/2139/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int T;
long long k, x, y, sum;
stack<int> s;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld", &k, &x);
    sum = 1ll << (k + 1); // 我真服了1ll
    y = sum - x;
    while (x != y) {
      if (x < y) {
        s.emplace(1);
        y -= x;
        x <<= 1;
      } else {
        s.emplace(2);
        x -= y;
        y <<= 1;
      }
    }
    printf("%d\n", (int)s.size());
    for (; !s.empty(); s.pop())
      printf("%d ", s.top());
    putchar('\n');
  }
  return 0;
}