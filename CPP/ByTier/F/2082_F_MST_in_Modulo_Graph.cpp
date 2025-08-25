/*
 * Problem URL : https://codeforces.com/problemset/problem/2082/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
namespace qGet {
const int sz = 1 << 18;
char buf[sz], *S, *T;
inline char gc() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, sz, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
struct Rd {
  Rd &operator>>(int &x) {
    x = 0;
    char c = gc();
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = gc();
    return *this;
  }
} cin;
} // namespace qGet
namespace qPut {
const int sz = 1 << 11;
char buf[sz], *S = buf, *T = buf + sz;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void pc(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct Exi {
  ~Exi() { flush(); }
} exi;
struct Wt {
  Wt &operator<<(int x) {
    if (!x) {
      pc('0');
      pc('\n');
      return *this;
    }
    static int sta[8];
    int tp = 0;
    while (x) {
      sta[tp++] = x % 10;
      x /= 10;
    }
    while (tp)
      pc('0' + sta[--tp]);
    pc('\n');
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet::cin
#define cout qPut::cout
#define rsz resize
#define vi vector<int>
using namespace std;
int main() {
  int sz = 8e6, t;
  cin >> t;
  vi a;
  vector<pair<int, int>> edge;
  edge.reserve(sz);
  vi nx;
  nx.reserve(sz);
  vi hd, p;
  auto fd = [&](int n, auto &&fd) -> int {
    return p[n] < 0 ? n : p[n] = fd(p[n], fd);
  };
  auto jo = [&](int a, int b) -> bool {
    a = fd(a, fd);
    b = fd(b, fd);
    if (a == b)
      return 0;
    if (p[a] > p[b])
      swap(a, b);
    p[a] += p[b];
    p[b] = a;
    return 1;
  };
  while (t--) {
    int n;
    cin >> n;
    a.rsz(n);
    for (auto &x : a)
      cin >> x;
    n = *max_element(a.begin(), a.end());
    vector<bool> has(++n);
    for (int x : a)
      has[x] = 1;
    vi nxt(n);
    int cnt = -1;
    for (int i = n - 1; i; i--)
      has[i] ? cnt++, nxt[i] = i : nxt[i] = nxt[i + 1];
    int m = (n + 1) / 2, tt = 0;
    edge.rsz(1);
    nx.rsz(1);
    hd.assign(m, 0);
    p.assign(n, -1);
    auto add = [&](int u, int v) {
      int c = max(u, v) % min(u, v);
      if (!c) {
        if (jo(u, v))
          cnt--;
        return;
      }
      edge.emplace_back(u, v);
      nx.push_back(hd[c]);
      hd[c] = ++tt;
    };
    for (int i = 1; i < n - 1; i++)
      if (has[i]) {
        add(i, nxt[i + 1]);
        for (int j = i + i; j < n; j += i)
          add(i, nxt[j]);
      }
    if (cnt <= 0) {
      cout << 0;
      continue;
    }
    int ans = 0;
    [&] {
      for (int c = 1; c < m; c++)
        for (int e = hd[c]; e; e = nx[e]) {
          auto [u, v] = edge[e];
          if (jo(u, v)) {
            ans += c;
            if (!--cnt)
              return;
          }
        }
    }();
    cout << ans;
  }
}