// Problem: CF 2040 D - Non Prime Tree
// https://codeforces.com/contest/2040/problem/D

/*
 * Problem: D. Non Prime Tree
 * Algorithm: DFS traversal with greedy assignment of values, using sieve for prime checking
 * Time Complexity: O(n * sqrt(max_val) + n) where max_val ~ 2 * n, due to sieve and DFS
 * Space Complexity: O(n) for storing tree structure, degree array, and auxiliary arrays
 * 
 * Approach:
 * - Build a tree from input edges.
 * - Find a centroid-like node (node with maximum degree) to use as root.
 * - Assign values from [1, 2*n] to nodes greedily such that for each edge,
 *   |a[u] - a[v]| is not a prime number.
 * - Use sieve to precompute primes up to 400000.
 * - Shuffle available values and process DFS to assign numbers using constraint.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#define EL puts("Elaina")
typedef long long ll;
using namespace std;
namespace IO {
const int siz = 1 << 18;
char buf[siz], *p1, *p2;
inline char getc() {
  return p1 == p2 && (p2 = buf + fread(p1 = buf, 1, siz, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
inline int read() {
  int x = 0;
  char ch = getc();
  while (!isdigit(ch))
    ch = getc();
  while (isdigit(ch))
    x = x * 10 + (ch ^ 48), ch = getc();
  return x;
}
} // namespace IO
using IO::read;
mt19937 rnd((ll) new char);
const int maxn = 4e5 + 3;
bitset<maxn> vis;
inline void sieve(const int n = 400000) {
  vis[1] = 1;
  for (int i = 2; i * i <= n; ++i)
    if (!vis[i])
      for (int j = i + i; j <= n; j += i)
        vis[j] = 1;
}
struct edge {
  int to, next;
} e[maxn << 1];
int len, head[maxn], deg[maxn];
inline void insert(int u, int v) { e[++len] = {v, head[u]}, head[u] = len; }
int n, a[maxn];
vector<int> vec;
inline void dfs(int u, int fa) {
  for (int i = head[u], j = 0; i; i = e[i].next)
    if (e[i].to != fa) {
      for (; j < vec.size(); ++j)
        if (vis[abs(a[u] - vec[j])]) {
          a[e[i].to] = vec[j], swap(vec[j], vec.back()), vec.pop_back();
          break;
        }
      dfs(e[i].to, u);
    }
}
inline void MyDearMoments() {
  n = read(), len = 0, vec.clear();
  memset(deg + 1, 0, n * sizeof(int));
  memset(head + 1, 0, n * sizeof(int));
  for (int i = 1, x, y; i < n; ++i)
    insert(x = read(), y = read()), insert(y, x), ++deg[x], ++deg[y];
  int root = 1;
  for (int i = 2; i <= n; ++i)
    if (deg[i] > deg[root])
      root = i;
  vec.resize(n << 1), iota(vec.begin(), vec.end(), 1),
      shuffle(vec.begin(), vec.end(), rnd);
  a[root] = vec.back(), vec.pop_back();
  dfs(root, 0);
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i]);
  puts("");
}
int main() {
  sieve();
  int T = read();
  while (T--)
    MyDearMoments();
  return 0;
}


// https://github.com/VaHiX/CodeForces/