// Problem: CF 1923 E - Count Paths
// https://codeforces.com/contest/1923/problem/E

/*
Algorithm: DFS traversal on tree to count beautiful paths
Techniques: 
  - Tree DFS with backtracking
  - Color-based counting using auxiliary array
  - Path counting with prefix sums approach

Time Complexity: O(n) per test case, where n is the number of vertices
Space Complexity: O(n) for storing tree structure and auxiliary arrays

This solution uses DFS to traverse the tree. For each vertex, it maintains a count
of how many times its color has appeared in the path from root to current vertex.
When visiting a child node in DFS, it adds the count of paths ending at that node,
then updates the count. This effectively counts all valid paths that start and 
end with same color and no intermediate vertex has that color.
*/
#include <stdio.h>
#include <string>

using namespace std;
#ifdef int
#define __defined_int_to_long_long
#undef int
#endif
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#endif
#define USE_FREAD
namespace lib {
#ifndef LIB_STRING
using string = std::string;
#endif
#ifdef USE_FREAD
template <const long long MAXSIZE, const long long MAX_ITEM_SZ = 500>
#endif
struct IO {
#ifdef USE_FREAD
#ifdef __linux__
  struct stat s;
  char *c;
#else
  char buf[MAXSIZE], *p1, *p2;
#endif
  char pbuf[MAXSIZE], *pp;
#ifdef __linux__
  IO() : pp(pbuf) {
    fstat(0, &s);
    c = (char *)mmap(nullptr, s.st_size, 1, 2, 0, 0);
  }
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}
#endif
  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#ifdef __linux__
  inline char gc() { return *c++; }
#else
  inline char gc() {
    if (p1 == p2)
      p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? '\0' : *p1++;
  }
#endif
  inline void sync() {
    fwrite(pbuf, 1, MAXSIZE, stdout);
    pp = pbuf;
  }
#else
  inline void sync() {}
  inline char gc() { return getchar(); }
#endif
  char floatFormat[10] = "%.6f", doubleFormat[10] = "%.6lf";
  inline bool blank(char ch) { return ch <= 32 or ch == 127; }
  inline bool isd(char x) { return (x >= '0' and x <= '9'); }
  inline IO &setprecision(int d) {
    sprintf(floatFormat, "%%.%df", d);
    sprintf(doubleFormat, "%%.%dlf", d);
    return *this;
  }
  string input(int reserve = 0) {
    char c = gc();
    string res = "";
    res.reserve(reserve);
    while ((c && !blank(c)) || c == ' ') {
      res.push_back(c);
      c = gc();
    }
    return res;
  }
  template <class T> inline void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; not isd(ch); ch = gc())
      if (ch == '-')
        sign = 1;
    for (; isd(ch); ch = gc())
      x = x * 10 + (ch ^ 48);
    if (ch == '.')
      for (ch = gc(); isd(ch); ch = gc())
        tmp *= .1f, x += tmp * (ch ^ 48);
    if (sign)
      x = -x;
  }
  inline void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc())
      ;
    for (; not blank(ch); ch = gc())
      *s++ = ch;
    *s = 0;
  }
  inline void readln(char *s) {
    char c = gc();
    while ((c && !blank(c)) || c == ' ') {
      *(s++) = c;
      c = gc();
    }
    *s = 0;
  }
  inline void readln(string &res, int reserve = 0) {
    char c = gc();
    string().swap(res);
    res.reserve(reserve);
    while ((c && !blank(c)) || c == ' ') {
      res.push_back(c);
      c = gc();
    }
  }
  inline void read(char &c) {
    for (c = gc(); blank(c); c = gc())
      ;
  }
  inline void read(string &s) {
    string().swap(s);
    char ch = gc();
    for (; blank(ch); ch = gc())
      ;
    for (; not blank(ch); ch = gc())
      s.push_back(ch);
  }
  template <class T, class... Types> inline void read(T &x, Types &...args) {
    read(x);
    read(args...);
  }
  template <class T> inline void scan(const T &x) { read(*x); }
  template <class T, class... Types>
  inline void scan(const T &x, const Types &...args) {
    read(*x);
    scan(args...);
  }
  inline void push(const char &c) {
#ifdef USE_FREAD
    if (pp - pbuf == MAXSIZE)
      sync();
    *pp++ = c;
#else
    putchar(c);
#endif
  }
  inline void write(const double x) {
#ifdef USE_FREAD
    if (pp - pbuf >= MAXSIZE - MAX_ITEM_SZ)
      sync();
    pp += sprintf(pp, doubleFormat, x);
#endif
#ifndef USE_FREAD
    printf(doubleFormat, x);
#endif
  }
  inline void write(const float x) {
#ifdef USE_FREAD
    if (pp - pbuf >= MAXSIZE - MAX_ITEM_SZ)
      sync();
    pp += sprintf(pp, floatFormat, x);
#endif
#ifndef USE_FREAD
    printf(floatFormat, x);
#endif
  }
  inline void write(const char c) { push(c); }
  inline void write(const string &s) {
    for (auto i : s)
      push(i);
  }
  inline void write(const char *s) {
    for (; *s; ++s)
      push(*s);
  }
  template <class T> inline void write(T x) {
    static char sta[40];
    int top = 0;
    if (x < 0) {
      push('-'), sta[top++] = (-(x % 10)) ^ 48, x = -(x / 10);
      if (x == 0) {
        push(sta[--top]);
        return;
      }
    }
    do {
      sta[top++] = x % 10 ^ 48, x /= 10;
    } while (x);
    while (top)
      push(sta[--top]);
  }
  template <class T = int> inline T get() {
    T x;
    read(x);
    return x;
  }
  template <class T> inline IO &operator>>(T &x) {
    read(x);
    return *this;
  }
  template <class T> inline IO &operator<<(const T &x) {
    write(x);
    return *this;
  }
};
IO
#ifdef USE_FREAD
    <1048576>
#endif
        io;
} // namespace lib
#ifdef __defined_int_to_long_long
#undef __defined_int_to_long_long
#define int long long
#endif
using namespace lib;
#define int long long
#define cin io
#define cout io
#define endl '\n'
const int N = 2e5 + 5;
struct edge {
  int to;
  int nxt;
} e[N * 2];
int head[N], c[N], tot, dp[N], t[N];
int n;
void add(int u, int v) {
  e[++tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot;
}
int ans = 0;
void dfs(int u, int pa) {
  int cu = c[u];
  int num = t[cu];
  ans += num;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == pa)
      continue;
    t[cu] = 1;
    dfs(v, u);
  }
  t[cu] = num + 1;
}
signed main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      head[i] = 0;
      t[i] = 0;
      ans = 0;
    }
    for (int i = 1; i <= n; i++) {
      cin >> c[i];
    }
    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      add(u, v);
      add(v, u);
    }
    dfs(1, 0);
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/