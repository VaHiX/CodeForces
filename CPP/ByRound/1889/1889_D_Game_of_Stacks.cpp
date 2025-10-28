// Problem: CF 1889 D - Game of Stacks
// https://codeforces.com/contest/1889/problem/D

/*
Algorithm: Tarjan's algorithm with stack simulation
Time Complexity: O(n + m) where n is number of stacks and m is total elements
Space Complexity: O(n + m) for storing stacks and auxiliary arrays

This solution simulates the recursive `get` function using an explicit stack.
It uses a modified version of Tarjan's algorithm to detect cycles and compute
the result for each node. The key insight is that the `get` function forms
a directed graph where each node points to the next node in the chain. When 
a cycle is detected, we process all nodes in the cycle to assign their results.

The process tracks:
- `js`: current index in each stack
- `ans`: result for each stack
- `on`: indicates if a node is on the stack
- `stack`: explicit stack for simulation
*/
#include <ctype.h>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <type_traits>

using namespace std;
using Int = long long;
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &a) {
  return os << "(" << a.first << ", " << a.second << ")";
};
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) {
  const int sz = as.size();
  os << "[";
  for (int i = 0; i < sz; ++i) {
    if (i >= 256) {
      os << ", ...";
      break;
    }
    if (i > 0) {
      os << ", ";
    }
    os << as[i];
  }
  return os << "]";
}
template <class T> void pv(T a, T b) {
  for (T i = a; i != b; ++i)
    cerr << *i << " ";
  cerr << endl;
}
template <class T> bool chmin(T &t, const T &f) {
  if (t > f) {
    t = f;
    return true;
  }
  return false;
}
template <class T> bool chmax(T &t, const T &f) {
  if (t < f) {
    t = f;
    return true;
  }
  return false;
}
#define COLOR(s) ("\x1b[" s "m")
struct Scanner {
  FILE *fp = nullptr;
  char line[(1 << 15) + 1];
  size_t st = 0, ed = 0;
  void reread() {
    memmove(line, line + st, ed - st);
    ed -= st;
    st = 0;
    ed += fread(line + ed, 1, (1 << 15) - ed, fp);
    line[ed] = '\0';
  }
  bool succ() {
    while (true) {
      if (st == ed) {
        reread();
        if (st == ed)
          return false;
      }
      while (st != ed && isspace(line[st]))
        st++;
      if (st != ed)
        break;
    }
    if (ed - st <= 50)
      reread();
    return true;
  }
  template <class T, enable_if_t<is_same<T, string>::value, int> = 0>
  bool read_single(T &ref) {
    if (!succ())
      return false;
    while (true) {
      size_t sz = 0;
      while (st + sz < ed && !isspace(line[st + sz]))
        sz++;
      ref.append(line + st, sz);
      st += sz;
      if (!sz || st != ed)
        break;
      reread();
    }
    return true;
  }
  template <class T, enable_if_t<is_integral<T>::value, int> = 0>
  bool read_single(T &ref) {
    if (!succ())
      return false;
    bool neg = false;
    if (line[st] == '-') {
      neg = true;
      st++;
    }
    ref = T(0);
    while (isdigit(line[st])) {
      ref = 10 * ref + (line[st++] - '0');
    }
    if (neg)
      ref = -ref;
    return true;
  }
  template <class T> bool read_single(vector<T> &ref) {
    for (auto &d : ref) {
      if (!read_single(d))
        return false;
    }
    return true;
  }
  void read() {}
  template <class H, class... T> void read(H &h, T &...t) {
    bool f = read_single(h);
    assert(f);
    read(t...);
  }
  Scanner(FILE *_fp) : fp(_fp) {}
};
struct Printer {
public:
  template <bool F = false> void write() {}
  template <bool F = false, class H, class... T>
  void write(const H &h, const T &...t) {
    if (F)
      write_single(' ');
    write_single(h);
    write<true>(t...);
  }
  template <class... T> void writeln(const T &...t) {
    write(t...);
    write_single('\n');
  }
  void flush() {
    fwrite(line, 1, pos, fp);
    pos = 0;
  }
  Printer(FILE *_fp) : fp(_fp) {}
  ~Printer() { flush(); }

private:
  static constexpr size_t SIZE = 1 << 15;
  FILE *fp;
  char line[SIZE], small[50];
  size_t pos = 0;
  void write_single(const char &val) {
    if (pos == SIZE)
      flush();
    line[pos++] = val;
  }
  template <class T, enable_if_t<is_integral<T>::value, int> = 0>
  void write_single(T val) {
    if (pos > (1 << 15) - 50)
      flush();
    if (val == 0) {
      write_single('0');
      return;
    }
    if (val < 0) {
      write_single('-');
      val = -val;
    }
    size_t len = 0;
    while (val) {
      small[len++] = char('0' + (val % 10));
      val /= 10;
    }
    for (size_t i = 0; i < len; i++) {
      line[pos + i] = small[len - 1 - i];
    }
    pos += len;
  }
  void write_single(const string &s) {
    for (char c : s)
      write_single(c);
  }
  void write_single(const char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++)
      write_single(s[i]);
  }
  template <class T> void write_single(const vector<T> &val) {
    auto n = val.size();
    for (size_t i = 0; i < n; i++) {
      if (i)
        write_single(' ');
      write_single(val[i]);
    }
  }
  void write_single(long double d) {
    {
      long long v = d;
      write_single(v);
      d -= v;
    }
    write_single('.');
    for (int _ = 0; _ < 8; _++) {
      d *= 10;
      long long v = d;
      write_single(v);
      d -= v;
    }
  }
};
Scanner sc(stdin);
Printer pr(stdout);
int N;
vector<int> D;
vector<vector<int>> G;
int main() {
  {
    sc.read(N);
    D.resize(N);
    G.resize(N);
    for (int u = 0; u < N; ++u) {
      sc.read(D[u]);
      G[u].resize(D[u]);
      for (int j = 0; j < D[u]; ++j) {
        sc.read(G[u][j]);
        --G[u][j];
      }
      reverse(G[u].begin(), G[u].end());
    }
    vector<int> js(N, 0), ans(N, -1), on(N, 0);
    vector<int> stack;
    stack.reserve(N);
    auto clear = [&](int t) -> void {
      for (; !stack.empty(); stack.pop_back()) {
        const int w = stack.back();
        ans[w] = t;
        on[w] = 0;
      }
    };
    for (int s = 0; s < N; ++s)
      if (!~ans[s]) {
        stack.push_back(s);
        on[s] = 1;
        for (; !stack.empty();) {
          const int u = stack.back();
          if (js[u] < D[u]) {
            const int v = G[u][js[u]];
            if (on[v]) {
              for (int w; (w = stack.back()) != v; stack.pop_back()) {
                ++js[w];
                on[w] = 0;
              }
              ++js[v];
            } else if (~ans[v]) {
              clear(ans[v]);
            } else {
              stack.push_back(v);
              on[v] = 1;
            }
          } else {
            clear(u);
          }
        }
      }
    for (int u = 0; u < N; ++u) {
      if (u)
        printf(" ");
      printf("%d", ans[u] + 1);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/