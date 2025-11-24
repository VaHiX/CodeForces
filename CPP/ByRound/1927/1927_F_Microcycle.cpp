// Problem: CF 1927 F - Microcycle
// https://codeforces.com/contest/1927/problem/F

/*
Purpose: This program finds a simple cycle in an undirected weighted graph such that the weight of the lightest edge in the cycle is minimized.

Algorithm:
- Uses Union-Find (Disjoint Set Union) to build a Minimum Spanning Tree (MST) by sorting edges in descending order.
- Then, for each edge not in the MST, it attempts to form a cycle by finding a path between the two endpoints using DFS.
- The DFS is used to trace back the path, and once a cycle is found, it outputs the minimum weight edge in that cycle.

Time Complexity: O(m * α(n) + m * n), where α(n) is the inverse Ackermann function.
Space Complexity: O(n + m), for storing graph and Union-Find structures.

*/
#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;
const int N = 3e5 + 10;
int t, n, m, f[N], flag, st[N], top;
int ver[N << 1], head[N], tot = 1, Next[N << 1], edge[N << 1];
struct node {
  int x, y, z, id;
} e[N];

// Function to add an undirected edge to the adjacency list.
void add(int x, int y, int z) {
  ver[++tot] = y;
  Next[tot] = head[x];
  head[x] = tot;
  edge[tot] = z;
}

// Comparator to sort edges in descending order of weight.
bool cmp(node x, node y) { return x.z > y.z; }

// Find operation with path compression for Union-Find.
int get(int x) {
  if (x == f[x])
    return x;
  else
    return f[x] = get(f[x]);
}

// DFS to find a path from x to t, avoiding specified edges.
void dfs(int x, int pre, int t) {
  st[++top] = x;
  if (x == t) {
    flag = 1;
    return;
  }
  for (int i = head[x]; i; i = Next[i]) {
    if (i == pre || i == (pre ^ 1)) // Skip the edge that leads back or its reverse
      continue;
    int y = ver[i];
    dfs(y, i, t);
    if (flag)
      return;
  }
  if (!flag)
    top--;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    tot = 1;
    for (int i = 1; i <= n; i++)
      f[i] = i, head[i] = 0;
    for (int i = 1; i <= m; i++) {
      e[i].id = 0;
      scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
    }
    sort(e + 1, e + m + 1, cmp);
    int cnt = n;
    for (int i = 1; i <= m; i++) {
      int x = e[i].x, y = e[i].y, z = e[i].z;
      int xx = get(x), yy = get(y);
      if (xx == yy)
        continue;
      f[xx] = yy;
      e[i].id = 1; // Mark edge as being in MST
      cnt--;
      add(x, y, z), add(y, x, z);
      if (cnt == 1)
        break;
    }
    flag = top = 0;
    for (int i = m; i >= 1; i--) {
      if (e[i].id)
        continue;
      int x = e[i].x, y = e[i].y;
      int xx = get(x), yy = get(y);
      if (xx == yy) { // If they are in the same component
        dfs(x, 0, y); // Find a path between x and y
        printf("%d %d\n", e[i].z, top);
        for (int j = 1; j <= top; j++)
          printf("%d ", st[j]);
        printf("\n");
        break;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/