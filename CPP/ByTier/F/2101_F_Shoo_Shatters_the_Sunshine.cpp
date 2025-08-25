/*
 * Problem URL : https://codeforces.com/problemset/problem/2101/F
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#include <cassert>

using u64 = unsigned long long;
using i64 = long long;

const int P = 998244353;

int add(int x, int y) {
  int result = x + y >= P ? x + y - P : x + y;
  assert(result >= 0 && result < P);
  return result;
}

int sub(int x, int y) {
  int result = x < y ? x - y + P : x - y;
  assert(result >= 0 && result < P);
  return result;
}

int mul(int x, int y) {
  u64 product = (u64)x * y;
  int result = product % P;
  assert(result >= 0 && result < P);
  return result;
}

int fpow(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1)
      ans = mul(ans, x);
    y >>= 1;
    x = mul(x, x);
  }
  assert(ans >= 0 && ans < P);
  return ans;
}

void run() {
  int n;
  std::cin >> n;

  std::vector<int> pw2(n + 1), pw3(n + 1), t(n + 1), s(n + 1);
  pw2[0] = pw3[0] = t[0] = s[0] = 1;
  for (int i = 1; i <= n; i++) {
    pw2[i] = mul(pw2[i - 1], 2);
    assert(pw2[i] >= 0 && pw2[i] < P);
    pw3[i] = mul(pw3[i - 1], 3);
    assert(pw3[i] >= 0 && pw3[i] < P);
    t[i] = mul(pw3[i], fpow(pw2[i], P - 2));
    assert(t[i] >= 0 && t[i] < P);
    s[i] = add(s[i - 1], t[i]);
    assert(s[i] >= 0 && s[i] < P);
  }

  std::vector<std::vector<int>> adj(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    assert(u >= 0 && u < n);
    assert(v >= 0 && v < n);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  std::vector<std::vector<int>> dis(n, std::vector<int>(n, -1));
  for (int s = 0; s < n; s++) {
    std::queue<int> q;
    q.push(s);
    dis[s][s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : adj[u]) {
        if (dis[s][v] == -1) {
          dis[s][v] = dis[s][u] + 1;
          q.push(v);
        }
      }
    }
    for (int v = 0; v < n; v++) {
      assert(dis[s][v] != -1);
    }
  }

  auto brute = [&]() {
    int ret = 0;
    for (int i = 0; i < pw3[n]; i++) {
      std::vector<int> col(n);
      int x = i;
      for (int j = 0; j < n; j++) {
        col[j] = x % 3;
        assert(col[j] >= 0 && col[j] < 3);
        x /= 3;
      }
      int mx = 0;
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if ((col[j] ^ col[k]) == 3) {
            mx = std::max(mx, dis[j][k]);
          }
        }
      }
      ret += mx;
    }
    return ret;
  };

  int ans = 0;

  auto solve = [&](std::vector<std::pair<int, int>> w, int extra) -> void {
    sort(w.begin(), w.end());
    for (int i = 1; i < (int)w.size(); ++i) {
      assert(w[i].first >= w[i - 1].first);
    }
    std::vector<int> ns(n);
    for (int i = 0; i < n; i++) {
      ns[i] = mul(w[i].first, t[i]);
      if (i)
        ns[i] = add(ns[i], ns[i - 1]);
    }
    for (int l = 0, r; l < (int)w.size(); l = r + 1) {
      r = l;
      while (r + 1 < (int)w.size() && w[l].first == w[r + 1].first)
        ++r;
      assert(r >= l);
      int len = r - l + 1;
      int c1 = sub(pw3[len], 2 * len + 1);
      int c2 = mul(sub(pw2[len], len + 1), 2);
      c1 = sub(c1, c2);
      int last = -1, same = 0;
      for (int i = l; i <= r; i++) {
        if (w[i].second != last) {
          if (same > 0) {
            int t1 = sub(pw3[same], 2 * same + 1);
            int t2 = mul(sub(pw2[same], same + 1), 2);
            t1 = sub(t1, t2);
            c1 = sub(c1, t1);
            c2 = sub(c2, t2);
          }
          last = w[i].second;
          same = 1;
        } else
          ++same;
        if (i == r) {
          int t1 = sub(pw3[same], 2 * same + 1);
          int t2 = mul(sub(pw2[same], same + 1), 2);
          t1 = sub(t1, t2);
          c1 = sub(c1, t1);
          c2 = sub(c2, t2);
          break;
        }
      }
      ans = add(ans, mul(mul(w[l].first * 2 + extra, c1), pw3[l]));
      if (l) {
        int coef = mul(c2, pw2[l - 1]);
        ans = add(ans, mul(w[l].first + extra, mul(s[l - 1], coef)));
        ans = add(ans, mul(ns[l - 1], coef));
      }
    }
  };

  for (int u = 0; u < n; u++) {
    std::vector<std::pair<int, int>> vec;
    for (int i = 0; i < n; i++) {
      if (i == u) {
        vec.push_back({0, 0});
        continue;
      }
      assert(!adj[u].empty());
      int id = adj[u][0];
      for (auto v : adj[u]) {
        if (dis[i][v] < dis[i][id]) {
          id = v;
        }
      }
      vec.push_back({dis[i][u], id});
    }
    solve(vec, 0);
    for (auto v : adj[u]) {
      if (u < v) {
        std::vector<std::pair<int, int>> vec;
        for (int i = 0; i < n; i++) {
          if (dis[u][i] < dis[v][i]) {
            vec.push_back({dis[u][i], u});
          } else {
            vec.push_back({dis[v][i], v});
          }
        }
        solve(vec, 1);
      }
    }
  }

  std::cout << ans << "\n";
  // std::cerr << brute() << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    run();
  }
  return 0;
}