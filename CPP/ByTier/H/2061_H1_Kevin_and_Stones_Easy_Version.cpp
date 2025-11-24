// Problem: CF 2061 H1 - Kevin and Stones (Easy Version)
// https://codeforces.com/contest/2061/problem/H1

/*
H1. Kevin and Stones (Easy Version)
time limit per test4 seconds
memory limit per test512 megabytes

This is the easy version of the problem. The difference between the versions is that in this version,
you only need to determine whether a valid sequence of operations exists.

Algorithm:
- This solution uses a combination of bipartite matching and Union-Find (Disjoint Set Union) to model
  the possible movements of stones between vertices.
- It constructs two matchings:
    1. Matching from initial stone positions to target positions.
    2. Matching from target stone positions to initial positions.
- Then, it uses Union-Find to detect if the movement constraints are consistent with the graph structure.

Time Complexity: O(n * m + n^2)
Space Complexity: O(n + m)

*/

#include <iosfwd>
#include <stdio.h>
using namespace std;
const int N = 4005, M = 20005;
int n, m;
char a[N], b[N];
int p[N], q[N], k; // p & q store positions of '1's in strings a and b, k is count
int u[M], v[M]; // edges
int la[N], ne[M], en[M], idx; // adjacency list for graph
int vis[N], match[N]; // for matching algorithm
int lka[N], lkb[N], id[N]; // mapping for matching results
int fa[N], cnt[N]; // Union-Find and counter arrays

inline void Add(int a, int b) {
  ne[++idx] = la[a];     // link previous edge
  la[a] = idx;           // head pointer update
  en[idx] = b;           // store adjacent vertex
}

inline int Find(int u) {
  for (int i = la[u]; i; i = ne[i]) {   // iterate adjacency list
    int v = en[i];
    if (!vis[v]) {
      vis[v] = 1;
      if (!match[v] || Find(match[v])) {  // try augmenting path
        match[v] = u;
        return 1;
      }
    }
  }
  return 0;
}

inline int Match(int p[], int lk[]) {
  for (int i = 1; i <= n; i++)
    id[i] = match[i] = 0;   // reset matching data
  for (int i = 1; i <= k; i++)
    id[p[i]] = i;           // map p index to order in array
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++)
      vis[j] = 0;
    if (!Find(p[i]))         // check if valid match exists
      return 0;
  }
  for (int i = 1; i <= n; i++)
    if (match[i])
      lk[id[match[i]]] = i; // record matched target positions
  return 1;
}

inline int gfa(int i) { return i == fa[i] ? i : fa[i] = gfa(fa[i]); }

inline int Check(int d) {
  for (int i = 1; i <= n * 2; i++)
    cnt[i] = 0;
  for (int i = 1; i <= k; i++)
    cnt[gfa(p[i])]++;
  for (int i = 1; i <= k; i++)
    cnt[gfa(q[i] + d)]--;   // apply offset to match groups
  for (int i = 1; i <= n * 2; i++)
    if (cnt[i])
      return 0;
  return 1;
}

inline void Solve() {
  scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
  k = 0;
  for (int i = 1; i <= n; i++)
    if (a[i] == '1')        // collect initial stones
      p[++k] = i;
  k = 0;
  for (int i = 1; i <= n; i++)
    if (b[i] == '1')        // collect target stones
      q[++k] = i;

  for (int i = 1; i <= n; i++)
    la[i] = 0;
  idx = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u[i], &v[i]);
    Add(u[i], v[i]), Add(v[i], u[i]); // build bidirectional graph
  }

  int flag = 1;
  for (int i = 1; i <= n; i++)
    flag &= a[i] == b[i];   // fast check if already identical
  if (flag)
    return puts("YES"), void();
  if (!Match(p, lka) || !Match(q, lkb)) // check match possibility
    return puts("NO"), void();

  for (int i = 1; i <= n * 2; i++)
    fa[i] = i;             // initialize Union-Find
  for (int i = 1; i <= m; i++) {
    fa[gfa(u[i])] = gfa(v[i] + n);   // link u to v+n in Union-Find
    fa[gfa(v[i])] = gfa(u[i] + n);   // symmetric pairing
  }

  puts(Check(0) || Check(n) ? "YES" : "NO");// verify compatibility using both 0 and n offset cases
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/