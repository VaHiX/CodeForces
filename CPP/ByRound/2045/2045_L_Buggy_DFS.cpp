/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL f(LL n) { return (n - 2) * (n - 2) + 3 * (n - 3) + 1 + 2; }

LL k;

int n = 1;

vector<pair<int, int>> E;

int main() {
  scanf("%lld", &k);
  if ((k < 11) && (k & 1))
    puts("-1 -1");
  else {
    if (k & 1) {
      k -= 11;
      n = 4;
      E.push_back({1, 2});
      E.push_back({1, 4});
      E.push_back({2, 4});
      E.push_back({2, 3});
    }
    while (k) {
      if (k >= f(4)) {
        int l = 3, r = 40000;
        while (l < r) {
          int mid = (l + r + 1) >> 1;
          if (f(mid + 1) <= k)
            l = mid;
          else
            r = mid - 1;
        }
        k -= f(l + 1);
        E.push_back({1, n + 2});
        for (int i = n + 2; i < n + l; ++i)
          E.push_back({i, i + 1});
        for (int i = n + 2; i <= n + l; ++i)
          E.push_back({n + 1, i});
        n += l;
      } else
        E.push_back({1, ++n}), k -= 2;
    }
    printf("%d %d\n", n, (int)E.size());
    for (auto it : E)
      printf("%d %d\n", it.first, it.second);
  }

  return 0;
}