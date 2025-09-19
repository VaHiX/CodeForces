/*
 * Problem URL : https://codeforces.com/contest/2138/problem/C2
 * Submit Date : 2025-09-09
 */

#include <bitset>
#include <iostream>
#include <tuple>
#include <vector>

template <int N = 32>
int subsetsum(const std::vector<int> &a, int n, int x, int y) {
  if (n >= N) {
    return subsetsum<std::min(N << 1, 1 << 20)>(a, n, x, y);
  }

  std::bitset<N> dp;
  dp.reset();
  dp.set(0);

  for (int i : a) {
    dp = dp | (dp << i);
  }

  for (int i = 0; i <= n; ++i) {
    if (dp.test(i) && i <= x && n - i <= y)
      return 1;
  }

  return 0;
}

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> tree(n);

  for (int i = 1; i < n; ++i) {
    int p;
    std::cin >> p;
    tree[p - 1].push_back(i);
  }

  std::vector<int> d(n, 0), cnt(n, 0);
  int minLeaf = n - 1;

  for (int v = 0; v < n; ++v) {
    cnt[d[v]] += 1;
    if (tree[v].empty()) {
      minLeaf = std::min(minLeaf, d[v]);
    }
    for (int u : tree[v]) {
      d[u] = d[v] + 1;
    }
  }

  std::vector<int> items(n + 1, 0);
  int sum = 0;

  for (int i = 0; i <= minLeaf; ++i) {
    if (cnt[i] >= 1) {
      items[cnt[i]] += 1;
      sum += cnt[i];
    }
  }

  std::vector<int> a;

  for (int i = 1; i <= n; ++i) {
    while (items[i] >= 3) {
      items[2 * i] += 1;
      items[i] -= 2;
    }
    for (int j = 0; j < items[i]; ++j) {
      a.push_back(i);
    }
  }

  std::cout << minLeaf + subsetsum(a, sum, k, n - k) << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
