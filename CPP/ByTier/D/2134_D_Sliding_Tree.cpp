// Problem: CF 2134 D - Sliding Tree
// https://codeforces.com/contest/2134/problem/D

/*
D. Sliding Tree
Algorithms/Techniques: Tree diameter finding, DFS traversal, sliding operation optimization
Time Complexity: O(n) per test case
Space Complexity: O(n) 

This code finds the first sliding operation needed to convert a tree into a path.
It uses two depth-first searches (DFS) to find the tree's diameter and then 
determines which node to use as the center for the first sliding operation.

The key idea is:
1. Find one end of the longest path (diameter) in the tree
2. From that end, find the other end of the diameter
3. If the diameter length equals n-1, then it's already a path
4. Otherwise, find the appropriate node to perform the first sliding move

The implementation builds an adjacency list representation of the tree 
and uses DFS to compute parent and depth information.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n, rt, ed; // n: number of nodes, rt: first endpoint of diameter, ed: second endpoint
int num, fst[200010], lst[400010], to[400010]; // graph storage
int fa[200010], dep[200010], sz[200010]; // parent, depth, subtree size

void clear() {
  num = 0;
  for (int i = 1; i <= n; i++) {
    fst[i] = 0; // clear adjacency list
    fa[i] = 0;  // clear parent array
  }
}

void insert(int u, int v) { // add undirected edge between u and v
  lst[++num] = fst[u];   // link previous edge
  to[num] = v;          // store destination 
  fst[u] = num;         // update head of adjacency list
  lst[++num] = fst[v];   // reverse edge (undirected)
  to[num] = u;
  fst[v] = num;
}

int dfs(int x) { // find the farthest node from x, return it
  sz[x] = 0;    // reset subtree size
  int md = x;   // initialize max depth node
  for (int i = fst[x]; i; i = lst[i]) // iterate neighbors
    if (fa[x] != to[i]) { // avoid going back to parent
      fa[to[i]] = x;       // set parent
      dep[to[i]] = dep[x] + 1; // set depth
      sz[x]++;             // increment subtree size
      int nd = dfs(to[i]); // recurse on child
      if (dep[nd] > dep[md]) // update farthest node
        md = nd;
    }
  return md; // return farthest node from x
}

int main() {
  int T, u, v;  // number of test cases
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    clear();   // reset global arrays
    
    for (int i = 1; i < n; i++) { // read all edges
      scanf("%d%d", &u, &v);
      insert(u, v);  // build graph
    }
    
    rt = dfs(1);  // find one end of diameter
    
    // reset arrays for new DFS
    for (int i = 1; i <= n; i++) {
      fa[i] = 0;
      dep[i] = 0;
      sz[i] = 0;
    }
    
    ed = dfs(rt); // find other end of diameter
    
    if (dep[ed] == n - 1) { // if diameter equals n-1, tree is already a path
      puts("-1");
      continue;
    }
    
    // find the node to perform sliding operation on
    while (sz[fa[ed]] < 2)
      ed = fa[ed]; // traverse up until having at least 2 children
    
    // find suitable third vertex c for operation (a, b, c) where b is center
    for (int i = fst[fa[ed]]; i; i = lst[i]) // iterate neighbors of parent of ed
      if (fa[fa[ed]] != to[i] && ed != to[i]) { // avoid forbidden nodes
        printf("%d %d %d\n", fa[fa[ed]], fa[ed], to[i]); // output operation
        break;
      }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/