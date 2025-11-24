// Problem: CF 2062 E2 - The Game (Hard Version)
// https://codeforces.com/contest/2062/problem/E2

// Problem: E2. The Game (Hard Version)
// Algorithm: Tree DFS + Segment Tree / BIT + Set for node management
// Time Complexity: O(n log n) per test case
// Space Complexity: O(n) per test case
//
// Task: Find all nodes that Cirno can choose in her first turn such that she wins,
// assuming both players play optimally.
//
// Approach:
// - Build the tree from input.
// - For each node, store the subtree information (dfn, out).
// - Use a segment tree / BIT for efficient maximum queries and updates.
// - Process nodes in reverse order (from n to 1) using DFS traversal.
// - Maintain a set of dfs numbers to check valid moves.
// - Apply optimization logic to detect winning choices.

#include <algorithm>
#include <ctype.h>
#include <iterator>
#include <set>
#include <stdio.h>
#include <utility>
#include <vector>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
namespace qGet {
const int sz = 1 << 19;
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
const int sz = 1 << 17;
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
struct NTR {
  ~NTR() { flush(); }
} ztr;
struct Wt {
  Wt &operator<<(int x) {
    if (!x) {
      pc('0');
      return *this;
    }
    static int sta[6];
    int top = 0;
    while (x) {
      sta[top++] = x % 10;
      x /= 10;
    }
    while (top)
      pc('0' + sta[--top]);
    return *this;
  }
  Wt &operator<<(char c) {
    pc(c);
    return *this;
  }
} cout;
} // namespace qPut
#define cin qGet::cin
#define cout qPut::cout
#define rsz resize
#define vi vector<int>
int main() {
  int T, n, tt;
  cin >> T;
  vi v2, n2, h2, vr, nx, hd, dfn, out, c;
  auto cmx = [](int &a, int b) {
    if (b > a)
      a = b;
  };
  auto ask = [&](int x) {
    int res = 0;
    for (; x; x -= x & -x)
      cmx(res, c[x]);
    return res;
  };
  while (T--) {
    cin >> n;
    v2.rsz(2 * n);
    n2.rsz(2 * n);
    h2.assign(n + 1, 0);
    vr.rsz(n + 1);
    nx.rsz(n + 1);
    hd = h2;
    dfn.rsz(n + 1);
    out.rsz(n + 1);
    c = hd;
    vi ans;
    ans.reserve(n);
    tt = 0;
    auto add = [&](int a, int b) {
      vr[++tt] = b;
      nx[tt] = hd[a];
      hd[a] = tt;
    };
    for (int i = 1, t; i <= n; i++) {
      cin >> t;
      add(t, i);
    }
    tt = 0;
    auto a2 = [&](int a, int b) {
      v2[++tt] = b;
      n2[tt] = h2[a];
      h2[a] = tt;
    };
    for (int i = 1, p, q; i < n; i++) {
      cin >> p >> q;
      a2(p, q);
      a2(q, p);
    }
    tt = 0;
    auto dfs = [&](int x, int pa, auto &&dfs) -> void {
      dfn[x] = ++tt;
      for (int e = h2[x], y; e; e = n2[e])
        if ((y = v2[e]) != pa)
          dfs(y, x, dfs);
      out[x] = tt;
    };
    dfs(1, 0, dfs);
    int L = n + 1, R = 0;
    set<int> st;
    for (int i = n; i; i--) {
      if (!st.empty()) {
        for (int e = hd[i], x; e; e = nx[e]) {
          x = vr[e];
          // If x is within range of current segment [L,R], check if a move is possible
          if (dfn[x] <= L && out[x] >= R &&
              (*st.begin() < dfn[x] || *st.rbegin() > out[x]) &&
              out[x] >= ask(dfn[x] - 1))
            ans.push_back(x);
        }
        for (int e = hd[i], y; e; e = nx[e]) {
          y = vr[e];
          // Determine minimum and maximum dfs numbers in the active set
          int mn = *st.begin(), mx = *st.rbegin(), cl = dfn[y], cr = out[y];
          if (mn >= cl) {
            if (mx <= cr)
              continue;
            if (mn <= cr)
              mn = *st.upper_bound(cr);
          }
          if (mx >= cl && mx <= cr)
            mx = *(--st.lower_bound(cl));
          auto fun = [&](int a, int b) {
            if (a > b)
              swap(a, b);
            L = min(L, b);
            cmx(R, a);
            for (; a <= n; a += a & -a)
              cmx(c[a], b);
          };
          fun(mx, cl);
          if (mx != mn)
            fun(mn, cl);
        }
      }
      // Add current dfs number to set for processing
      for (int e = hd[i], z; e; e = nx[e])
        st.insert(dfn[z = vr[e]]);
    }
    sort(ans.begin(), ans.end());
    cout << (int)ans.size();
    for (int x : ans)
      cout << ' ' << x;
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/