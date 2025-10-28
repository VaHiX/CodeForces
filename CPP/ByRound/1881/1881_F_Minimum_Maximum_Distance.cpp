// Problem: CF 1881 F - Minimum Maximum Distance
// https://codeforces.com/contest/1881/problem/F

/*
 * Problem: Minimum Maximum Distance in a Tree
 * 
 * Algorithm: 
 *   - This solution computes the minimum eccentricity among all vertices in a tree,
 *     where eccentricity of a vertex is the maximum distance from that vertex to any of the marked vertices.
 *   - The approach uses two DFS traversals:
 *     1. First DFS from the first marked vertex to compute depths.
 *     2. Second DFS from the farthest marked vertex found in first traversal to compute depths again.
 *   - The result is the ceiling of half the maximum depth found in the second DFS, which corresponds to the radius of the tree
 *     with respect to the set of marked vertices.
 * 
 * Time Complexity: O(n) per test case, since each node is visited at most twice.
 * Space Complexity: O(n) for storing the tree structure and auxiliary arrays.
 */

#include <stdio.h>
#include <string.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define SWAP(T, A, B)                                                          \
  do {                                                                         \
    T t = A;                                                                   \
    A = B;                                                                     \
    B = t;                                                                     \
  } while (0)
#define ABS(X) ((X) > 0 ? (X) : -(X))
#define LOWBIT(X) ((X) & -(X))
#define RN 1000005
#define INF32 0x3f3f3f3f
#define INF8 0x3f
#define INF64 0x3f3f3f3f3f3f3f3fll

int head[RN], nxt[RN], to[RN], ai[RN], dep[RN];

// DFS to compute depth from a given root node
void dfs(int x, int fa) {
  for (int i = head[x]; i; i = nxt[i]) {
    int v = to[i];
    if (v != fa) {
      dep[v] = dep[x] + 1;
      dfs(v, x);
    }
  }
}

void run(void) {
  int n, k;
  scanf("%d%d", &n, &k);
  memset(head, 0, sizeof(int) * (n + 2));
  for (int i = 1; i <= k; i++) {
    scanf("%d", &ai[i]);
  }
  int ecnt = 0;
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    nxt[++ecnt] = head[u];
    to[ecnt] = v;
    head[u] = ecnt;
    nxt[++ecnt] = head[v];
    to[ecnt] = u;
    head[v] = ecnt;
  }
  dep[ai[1]] = 0;
  dfs(ai[1], 0);
  int now = 0, nowi = 0;
  for (int i = 1; i <= k; i++) {
    if (dep[ai[i]] > now) {
      now = dep[ai[i]];
      nowi = i;
    }
  }
  dep[ai[nowi]] = 0;
  dfs(ai[nowi], 0);
  int ans = 0;
  for (int i = 1; i <= k; i++) {
    if (dep[ai[i]] > ans) {
      ans = dep[ai[i]];
    }
  }
  printf("%d\n", (ans + 1) / 2);
}

int main(void) {
  int t = 1;
  scanf("%d", &t);
  while (t--) {
    run();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/