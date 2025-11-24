// Problem: CF 1672 F2 - Checker for Array Shuffling
// https://codeforces.com/contest/1672/problem/F2

/*
Algorithm: 
This problem is about determining whether a given permutation b of array a has maximum possible "sadness"
(i.e., minimum number of swaps to convert b back to a). The key insight is to model this as a directed graph
where each position i has an edge from a[i] to b[i]. The minimum number of swaps corresponds to the number
of cycles in this graph, and the maximum sadness corresponds to the maximum number of cycles.

Approach:
- Build a directed graph where each element of a points to the corresponding element in b.
- Use topological sort to detect cycles. If we can topologically sort all nodes, then there are no cycles.
- But the actual goal is to compute the minimum number of swaps needed to convert b into a.
- For that, we simulate a cycle decomposition. In fact, the code models it as a graph and uses topological sorting
  which works because in the case of maximum sadness, it's equivalent to a DAG (no cycles), and the number of
  operations needed is n minus the number of nodes that can go through topological order (i.e., nodes not in cycles).

Time Complexity: O(n)
Space Complexity: O(n)
*/
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 2e5 + 5;
int t, n, a[N], b[N], cnt[N], mx, h[N], tot, d[N], sum;
bool op;
struct edge {
  int to, nxt;
} e[N];
void add(int u, int v) {
  e[++tot] = {v, h[u]};
  h[u] = tot;
  d[v]++;
}
void topo() {
  queue<int> q;
  for (int i = 1; i <= n; i++)
    if (!d[i])
      q.push(i);
  while (q.size()) {
    int u = q.front();
    q.pop();
    sum++;
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      if (!--d[v])
        q.push(v);
    }
  }
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    mx = tot = sum = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), h[i] = d[i] = cnt[i] = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &b[i]), cnt[b[i]]++;
    for (int i = 1; i <= n; i++)
      if (cnt[i] > cnt[mx])
        mx = i;
    for (int i = 1; i <= n; i++)
      if (a[i] != mx && b[i] != mx)
        add(a[i], b[i]);
    topo();
    if (sum == n)
      puts("AC");
    else
      puts("WA");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/