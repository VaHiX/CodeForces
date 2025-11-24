// Problem: CF 1777 D - Score of a Tree
// https://codeforces.com/contest/1777/problem/D

/*
 * Problem: D. Score of a Tree
 *
 * Algorithm: 
 *   - This solution leverages the properties of tree DP and XOR operations to compute
 *     the total contribution of all possible initial node configurations.
 *   - For each node, we compute how many times it contributes to the sum S(t) over all t,
 *     which depends on how many descendants it has in the tree.
 *   - The final answer is computed using the formula:
 *     (2^(n-1)) * (sum of contributions of all nodes).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n)
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#define fw fwrite(obuf, p3 - obuf, 1, stdout)
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
#define putchar(x)                                                             \
  (p3 - obuf < 1 << 20 ? (*p3++ = (x)) : (fw, p3 = obuf, *p3++ = (x)))
#define il inline
using namespace std;
char buf[1 << 20], obuf[1 << 20], *p1 = buf, *p2 = buf, *p3 = obuf,
                                  str[20 << 2];
il int read() {
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getchar();
  return x;
}
template <typename T> il void write(T x, char sf = '\n') {
  if (x < 0)
    putchar('-'), x = ~x + 1;
  int top = 0;
  do
    str[top++] = x % 10, x /= 10;
  while (x);
  while (top)
    putchar(str[--top] + 48);
  if (sf ^ '#')
    putchar(sf);
}
constexpr int MAXN = 2e5 + 5, MOD = 1e9 + 7;
int T, n, head[MAXN], tot;
struct {
  int v, to;
} e[MAXN << 1];
il void addedge(int u, int v) {
  e[++tot] = {v, head[u]};
  head[u] = tot;
}
int pw2[MAXN], d[MAXN];
il void add(int &x, int y) { x = x + y >= MOD ? x + y - MOD : x + y; }
il int dfs(int u, int fno) {
  int res = 0;
  d[u] = 0;
  for (int i = head[u], v; i; i = e[i].to)
    if ((v = e[i].v) != fno) {
      add(res, dfs(v, u));
      d[u] = max(d[u], d[v]);
    }
  add(res, ++d[u]);  // Increment the number of nodes in subtree rooted at u
  return res;
}
int main() {
  pw2[0] = 1;
  for (int i = 1; i <= 2e5; i++)
    pw2[i] = pw2[i - 1] * 2 % MOD;
  T = read();
  while (T--) {
    n = read();
    for (int i = 1; i < n; i++) {
      int u = read(), v = read();
      addedge(u, v), addedge(v, u);
    }
    write(1ll * pw2[n - 1] * dfs(1, 0) % MOD);  // Final result: 2^(n-1) * sum of depths
    memset(head, 0, (n + 1) << 2);
    tot = 0;
  }
  return fw, 0;
}


// https://github.com/VaHiX/CodeForces/