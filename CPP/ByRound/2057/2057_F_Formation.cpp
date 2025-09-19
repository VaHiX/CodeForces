/*
 * Problem URL : https://codeforces.com/problemset/problem/2057/F
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

void solve() {
  int n, q, mx = 0;
  scanf("%d%d", &n, &q);
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  int las = *max_element(a.begin(), a.end());
  vector<int> que(q), ord(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d", &que[i]);
    ord[i] = i;
  }
  sort(ord.begin(), ord.end(),
       [&](int const &u, int const &v) { return que[u] < que[v]; });
  LL maxv = las + que[ord.back()] + 2;

  vector<tuple<int, int, LL>> eve;
  for (int i = 0; i < n; ++i) {
    LL low = 0, upp, sum = 0;
    for (int j = 0; j <= i; ++j) {
      low = max(low, (LL)a[i - j] << j);
      upp = j < i ? min((LL)a[i - j - 1] << (j + 1) | 1, maxv) : maxv;
      if (low >= upp)
        break;
      // assert(j <= 30);
      sum += a[i - j];
      if (low < las) {
        low = las;
        if (upp <= low)
          continue;
      }
      // printf("add #%d [%lld, %lld): %lld\n", j, low, upp, sum);
      eve.push_back({(int)low, j, sum});
      eve.push_back({(int)upp, j, -sum});
      mx = max(mx, j);
    }
  }
  sort(eve.begin(), eve.end(), greater<>());
  vector<multiset<LL>> cand(mx + 1);
  for (; !eve.empty() && las == get<0>(eve.back()); eve.pop_back()) {
    auto &[_, j, sum] = eve.back();
    if (sum < 0) {
      cand[j].erase(cand[j].find(-sum));
    } else {
      cand[j].insert(sum);
    }
  }
  auto calc = [&](int x) -> LL {
    // int xx = x;
    LL ret = LLONG_MAX, cur = 0;
    for (int i = 0; i <= mx; ++i, x = (x + 1) >> 1) {
      cur += x;
      if (!cand[i].empty())
        ret = min(ret, cur - *cand[i].rbegin());
      if (x == 1)
        break;
    }
    // printf("calc %d: %lld\n", xx, ret);
    return ret;
  };

  int pre = las;
  for (int i : ord) {
    // printf("i %d: %d\n", i, que[i]);
    while (!eve.empty() && calc(get<0>(eve.back()) - 1) <= que[i])
      for (las = get<0>(eve.back()), pre = -1;
           !eve.empty() && las == get<0>(eve.back()); eve.pop_back()) {
        auto &[_, j, sum] = eve.back();
        if (sum < 0) {
          cand[j].erase(cand[j].find(-sum));
        } else {
          cand[j].insert(sum);
        }
      }
    // assert(!eve.empty());
    int L = max(las - 1, pre), R = get<0>(eve.back()) - 1;
    while (L < R) {
      int M = L + ((R - L + 1) >> 1);
      if (calc(M) <= que[i]) {
        L = M;
      } else {
        R = M - 1;
      }
    }
    pre = que[i] = L;
  }
  for (int i = 0; i < q; ++i)
    printf("%d%c", que[i], " \n"[i == q - 1]);

  // puts("clear");
}

int main() {
  int T = 1;
  scanf("%d", &T);
  for (int Case = 1; Case <= T; ++Case) {
    // printf("Case #%d: ", Case);
    solve();
  }
  return 0;
}