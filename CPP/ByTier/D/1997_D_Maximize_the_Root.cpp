// Problem: CF 1997 D - Maximize the Root
// https://codeforces.com/contest/1997/problem/D

/*
Algorithm: 
- The problem is about maximizing the value at the root of a tree by performing operations that transfer value from a node to its subtree.
- Each operation on a node v adds 1 to v and subtracts 1 from all nodes in its subtree (excluding v).
- Key insight: We can think of this as a "flow" of value from children to parent.
- The algorithm uses DFS on the tree:
    - For each child of the root, compute the minimum value that can be achieved in its subtree.
    - For each subtree, recursively calculate the "minimum value" needed to be "passed up" to parent after applying operations.
    - At each node, we decide whether it's beneficial to pass up as much value as possible (by transferring) to maximize root value.
- The final answer is the initial value at root plus the accumulated "net gain" from all subtrees.

Time Complexity: O(n) per test case (each node visited once in DFS)
Space Complexity: O(n) for adjacency list and recursion stack
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int MAXN = 2e5 + 10;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
const int inf_int = 0x7f7f7f7f;
const long long inf_long = 0x7f7f7f7f7f7f7f7f;
const double eps = 1e-9;
char Buf[1 << 23], *P1 = Buf, *P2 = Buf;
#define getchar()                                                              \
  (P1 == P2 && (P2 = (P1 = Buf) + fread(Buf, 1, 1 << 23, stdin), P1 == P2)     \
       ? EOF                                                                   \
       : *P1++)
template <typename type> inline void read(type &x) {
  x = 0;
  bool f = false;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    f |= ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = x * 10 + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename type, typename... args>
inline void read(type &x, args &...y) {
  read(x), read(y...);
}
int t, n, ans, val[MAXN], k, head[MAXN];
struct node {
  int to, next;
} edge[MAXN << 1];
void build(int u, int v) {
  edge[++k].to = v;
  edge[k].next = head[u];
  head[u] = k;
}
int dfs(int u) {
  if (head[u] == 0)
    return val[u];
  int minn = inf_int;
  for (int i = head[u]; i; i = edge[i].next) {
    int v = edge[i].to;
    minn = min(minn, dfs(v));
  }
  if (val[u] < minn)
    return (val[u] + minn) >> 1;
  else
    return minn;
}
signed main() {
  read(t);
  while (t--) {
    read(n);
    for (int i = 1; i <= n; i++)
      read(val[i]);
    ans = inf_int;
    k = 0;
    for (int i = 1; i <= n; i++)
      head[i] = 0;
    for (int i = 2; i <= n; i++) {
      int u;
      read(u);
      build(u, i);
    }
    for (int i = head[1]; i; i = edge[i].next)
      ans = min(ans, dfs(edge[i].to));
    cout << val[1] + ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/