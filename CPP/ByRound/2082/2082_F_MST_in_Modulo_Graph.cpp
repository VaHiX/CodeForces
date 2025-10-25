// Problem: CF 2082 F - MST in Modulo Graph
// https://codeforces.com/contest/2082/problem/F

// F. MST in Modulo Graph
// Purpose: Given a complete graph with vertex weights, compute the minimum spanning tree (MST) 
// where edge weights are defined as max(p_x, p_y) mod min(p_x, p_y).
// Algorithms:
//   - Union-Find (Disjoint Set Union) for MST Kruskal's algorithm
//   - Optimized input/output using fast I/O
// Time Complexity: O(n * log n + n * α(n)) where α is inverse Ackermann function, 
//                  and n is maximum vertex weight
// Space Complexity: O(n) for auxiliary arrays and DSU
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

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
    return p[n] < 0 ? n : p[n] = fd(p[n], fd); // Find with path compression
  };
  auto jo = [&](int a, int b) -> bool {
    a = fd(a, fd);
    b = fd(b, fd);
    if (a == b)
      return 0;
    if (p[a] > p[b])
      swap(a, b); // Union by size
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
    int cnt = -1; // Count of connected components minus one
    for (int i = n - 1; i; i--)
      has[i] ? cnt++, nxt[i] = i : nxt[i] = nxt[i + 1];
    int m = (n + 1) / 2, tt = 0;
    edge.rsz(1);
    nx.rsz(1);
    hd.assign(m, 0); // Heads of linked list for buckets
    p.assign(n, -1); // DSU parent array
    auto add = [&](int u, int v) {
      int c = max(u, v) % min(u, v);
      if (!c) { // If remainder is zero, they are connected (can be merged)
        if (jo(u, v))
          cnt--;
        return;
      }
      edge.emplace_back(u, v);
      nx.push_back(hd[c]);
      hd[c] = ++tt; // Add to bucket
    };
    for (int i = 1; i < n - 1; i++)
      if (has[i]) {
        add(i, nxt[i + 1]);
        for (int j = i + i; j < n; j += i)
          add(i, nxt[j]);
      }
    if (cnt <= 0) { // Already all connected
      cout << 0;
      continue;
    }
    int ans = 0;
    [&] {
      for (int c = 1; c < m; c++)
        for (int e = hd[c]; e; e = nx[e]) {
          auto [u, v] = edge[e];
          if (jo(u, v)) { // Try to union these nodes
            ans += c;
            if (!--cnt) // If all connected
              return;
          }
        }
    }();
    cout << ans;
  }
}


// https://github.com/VaHiX/codeForces/