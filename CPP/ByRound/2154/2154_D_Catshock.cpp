// Problem: CF 2154 D - Catshock
// https://codeforces.com/contest/2154/problem/D

/*
 * Code Purpose: Solve the Catshock problem where we need to create a sequence of parkour instructions
 *               to guide a cat from node 1 to node n on a tree, regardless of the cat's choices.
 *               The instructions are:
 *               - 1: Move to an adjacent node (if any)
 *               - 2 u: Destroy node u and all adjacent edges
 *               Constraints: No two consecutive 2 instructions, and the total sequence length <= 3n.
 *
 * Algorithm/Techniques: 
 *   - DFS traversal to build adjacency list and compute depths
 *   - Post-order DFS to construct the solution sequence:
 *     - For each node, check if depth parity matches the current count of 1s
 *     - If not, add extra 1 moves to adjust
 *     - Then issue a 2 instruction to destroy the current node
 *
 * Time Complexity: O(n) per test case due to DFS traversals and linear processing
 * Space Complexity: O(n) for storing the tree structure and result sequence
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2 * 1e5 + 5;
int las[N * 2], nex[N * 2], h[N], cnt = 0;
int cnt2 = 0, cnt3 = 0;
void add(int x, int y) {
  las[++cnt2] = y;
  nex[cnt2] = h[x];
  h[x] = cnt2;
}
int d[N];
void dfs(int x, int fa) {
  for (int i = h[x]; i != 0; i = nex[i]) {
    if (las[i] == fa) {
      continue;
    }
    d[las[i]] = d[x] + 1;
    dfs(las[i], x);
  }
  return;
}
int t, n;
int ans[N * 3], res[N * 3];
void dfs2(int x, int fa) {
  for (int i = h[x]; i != 0; i = nex[i]) {
    if (las[i] == fa) {
      continue;
    }
    dfs2(las[i], x);
  }
  if (x == n) {
    return;
  }
  if (cnt3 % 2 != d[x] % 2) { // Adjust parity for move count vs depth parity
    ans[++cnt] = 1;
    ans[++cnt] = 1;
    cnt3 += 2;
  } else {
    ans[++cnt] = 1;
    cnt3++;
  }
  ans[++cnt] = 2;
  res[cnt] = x; // Store the node to be destroyed
  return;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      h[i] = 0;
    }
    cnt = 0;
    cnt2 = 0;
    cnt3 = 0;
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      add(x, y);
      add(y, x);
    }
    d[1] = 0;
    dfs(1, 0); // Compute depths using DFS
    dfs2(n, 0); // Build the instruction sequence using DFS
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; i++) {
      if (ans[i] == 1) {
        printf("1\n");
      } else {
        printf("2 %d\n", res[i]);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/