// Problem: CF 1882 D - Tree XOR
// https://codeforces.com/contest/1882/problem/D

/*
Algorithm: Tree Dynamic Programming with rerooting technique
Time Complexity: O(n)
Space Complexity: O(n)

This solution uses a two-pass DFS approach:
1. First DFS (dfs): Computes the cost of making all values equal when the tree is rooted at node 1.
   It calculates the total cost by considering the XOR of values at each edge and the size of subtrees.
2. Second DFS (dfs2): Uses rerooting to compute the minimum cost for all other root nodes.
   It leverages the formula: res[v] = res[u] + (a[u] ^ a[v]) * (n - siz[v] - siz[v])
   This formula effectively transfers the solution from root u to root v,
   adjusting for the change in subtree sizes and XOR differences.

The key idea is that when rerooting from node u to v, we adjust the cost
by considering how the XOR differences and subtree sizes change across the edge (u, v).
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <string>

namespace fastio {
namespace IO {
#ifndef LOCAL
constexpr auto maxn = 1 << 20;
char in[maxn], out[maxn], *p1 = in, *p2 = in, *p3 = out;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = in) + fread(in, 1, maxn, stdin), p1 == p2) ? EOF    \
                                                                      : *p1++)
#define flush() (fwrite(out, 1, p3 - out, stdout))
#define putchar(x) (p3 == out + maxn && (flush(), p3 = out), *p3++ = (x))
class Flush {
public:
  ~Flush() { flush(); }
} _;
#endif
namespace usr {
template <typename type> inline type read(type &x) {
  x = 0;
  bool flag(0);
  char ch = getchar();
  while (!isdigit(ch))
    flag ^= ch == '-', ch = getchar();
  while (isdigit(ch))
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return flag ? x = -x : x;
}
template <typename type> inline void write(type x) {
  x < 0 ? x = -x, putchar('-') : 0;
  static short Stack[50], top(0);
  do
    Stack[++top] = x % 10, x /= 10;
  while (x);
  while (top)
    putchar(Stack[top--] | 48);
}
inline char read(char &x) {
  do
    x = getchar();
  while (isspace(x));
  return x;
}
inline char write(const char &x) { return putchar(x); }
inline void read(char *x) {
  static char ch;
  read(ch);
  do
    *(x++) = ch;
  while (!isspace(ch = getchar()) && ~ch);
}
template <typename type> inline void write(type *x) {
  while (*x)
    putchar(*(x++));
}
inline void read(std::string &x) {
  static char ch;
  read(ch), x.clear();
  do
    x += ch;
  while (!isspace(ch = getchar()) && ~ch);
}
inline void write(const std::string &x) {
  for (int i = 0, len = x.length(); i < len; ++i)
    putchar(x[i]);
}
template <typename type, typename... T> inline void read(type &x, T &...y) {
  read(x), read(y...);
}
template <typename type, typename... T>
inline void write(const type &x, const T &...y) {
  write(x), putchar(' '), write(y...), sizeof...(y) ^ 1 ? 0 : putchar('\n');
}
template <typename type> inline void put(const type &x, bool flag = 1) {
  write(x), flag ? putchar('\n') : putchar(' ');
}
} // namespace usr
#ifndef LOCAL
#undef getchar
#undef flush
#undef putchar
#endif
} // namespace IO
using namespace IO::usr;
} // namespace fastio
using namespace fastio::IO::usr;
const int N = 2e5 + 7;
int t, n, a[N];
int head[N], nxt[N << 1], to[N << 1], edge_cnt;
void init() {
  edge_cnt = 0;
  memset(head, -1, (n + 1) * sizeof(int));
}
void add_edge(int u, int v) {
  to[edge_cnt] = v;
  nxt[edge_cnt] = head[u];
  head[u] = edge_cnt++;
}
long long res[N], siz[N];
void dfs(int u, int fa) {
  siz[u] = 1;
  for (int i = head[u]; ~i; i = nxt[i]) {
    int v = to[i];
    if (v == fa)
      continue;
    dfs(v, u);
    siz[u] += siz[v];
    res[1] += (a[u] ^ a[v]) * siz[v]; // Add cost for this edge
  }
}
void dfs2(int u, int fa) {
  for (int i = head[u]; ~i; i = nxt[i]) {
    int v = to[i];
    if (v == fa)
      continue;
    // Reroot from u to v, update res[v] based on res[u]
    res[v] = res[u] + (a[u] ^ a[v]) * (n - siz[v] - siz[v]);
    dfs2(v, u);
  }
}
void solve() {
  read(n), init();
  for (int i = 1; i <= n; ++i)
    read(a[i]);
  for (int i = 2, u, v; i <= n; ++i)
    read(u, v), add_edge(u, v), add_edge(v, u);
  res[1] = 0, dfs(1, 0), dfs2(1, 0);
  for (int i = 1; i <= n; ++i)
    put(res[i], i == n);
}
int main() {
  read(t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/