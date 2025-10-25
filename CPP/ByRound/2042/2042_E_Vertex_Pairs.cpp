// Problem: CF 2042 E - Vertex Pairs
// https://codeforces.com/contest/2042/problem/E

/*
E. Vertex Pairs
Algorithms/Techniques: Tree DFS, BFS, Graph Traversal, Greedy
Time Complexity: O(n)
Space Complexity: O(n)

This code solves the problem of selecting a connected subset of vertices in a tree such that:
- Each value from 1 to n appears on at least one selected vertex.
- The total cost (2^i for vertex i) is minimized.

Approach:
1. Build an undirected tree from input edges
2. For each color (value 1 to n), store its two occurrences in the tree
3. Run a DFS-based algorithm twice — once starting from one of the nodes with color 1, 
   and once starting from the other node with color 1.
4. For each traversal, decide whether to include or exclude each node based on connectivity and coverage constraints.
5. Pick the better result (lesser total cost) between two traversals.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n;
const int N = 2e5 + 5;
int col[N << 1];        // color of each vertex
int sc[N << 1];         // stores the other occurrence of a color
int tmp1[N];
struct et {
  int to, nxt;
} e[N << 2];            // edge list for adjacency
int head[N << 1], ecnt; // graph representation

// Add an undirected edge between u and v
void addedge(int u, int v) {
  e[++ecnt] = et{v, head[u]};
  head[u] = ecnt;
}

int fp[N << 1], lp[N << 1]; // first and last visit in DFS order for each node
int dfncnt;                 // DFS counter
#define y e[i].to               // shortcut to neighbor

int qzr_maxl[N << 1];       // max position of color occurrence seen so far
int fa[N << 1];             // parent array

// DFS to compute initial coverage and time stamps
void dfs1(int x, int father) {
  fa[x] = father;
  fp[x] = ++dfncnt;
  qzr_maxl[dfncnt] = qzr_maxl[dfncnt - 1];
  
  if (tmp1[col[x]]) {
    qzr_maxl[dfncnt] = max(qzr_maxl[dfncnt], tmp1[col[x]]);
  } else {
    tmp1[col[x]] = dfncnt;
  }
  
  for (int i = head[x]; i; i = e[i].nxt) {
    if (y == father) {
      continue;
    }
    dfs1(y, x);
  }
  lp[x] = dfncnt;
}

int used[N << 1];

// Mark the current node and all its ancestors if they are not yet marked
void pick(int x) {
  if (x == 0 || used[x] != 0) {
    return;
  }
  used[x] = 1;
  pick(fa[x]);
}

// Process subtree rooted at x and mark nodes which need to be erased
void erase(int x) {
  if (used[x] != 0) {
    return;
  }
  used[x] = -1;
  pick(sc[x]);   // Mark the corresponding node in another color
  for (int i = head[x]; i; i = e[i].nxt) {
    if (y == fa[x]) {
      continue;
    }
    erase(y);
  }
}

// Main logic to compute valid subset using DFS traversal
void work(int rt) {
  for (int i = 1; i <= n; ++i) {
    tmp1[i] = 0;   // reset color tracking
  }
  for (int i = 1; i <= n << 1; ++i) {
    used[i] = 0;   // reset usage array
  }
  dfncnt = 0;
  qzr_maxl[0] = 0;  // prefix max initialization
  
  dfs1(rt, 0);
  
  for (int i = n << 1; i; --i) {
    if (used[i] != 0) {
      continue;
    }
    
    // If current node was visited before or is not in the valid set
    if (fp[i] <= qzr_maxl[lp[i]]) {
      pick(i);   // mark this and ancestors to be included
    } else {
      erase(i);  // mark subtree as to be excluded
    }
  }
}

bool ans1[N << 1], ans2[N << 1]; // results of two traversals
int ans1cnt, ans2cnt;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  
  cin >> n;
  
  for (int i = 1; i <= n << 1; ++i) {
    cin >> col[i];
    
    // For each color, store its two positions
    if (tmp1[col[i]]) {
      sc[i] = tmp1[col[i]];
      sc[tmp1[col[i]]] = i;
    } else {
      tmp1[col[i]] = i;
    }
  }

  int rt1 = tmp1[1];   // start node for first traversal
  ecnt = 1;
  int inp1, inp2;
  
  // Read the edges of the tree
  for (int i = 1; i < n << 1; ++i) {
    cin >> inp1 >> inp2;
    addedge(inp1, inp2);
    addedge(inp2, inp1);
  }
  
  ans1cnt = ans2cnt = 0;
  
  work(rt1);   // first traversal
  
  for (int i = 1; i <= n << 1; ++i) {
    ans1[i] = (used[i] == 1);
    ans1cnt += (used[i] == 1);
  }
  
  rt1 = sc[rt1];  // second start node for second traversal
  work(rt1);   // second traversal
  
  for (int i = 1; i <= n << 1; ++i) {
    ans2[i] = (used[i] == 1);
    ans2cnt += (used[i] == 1);
  }
  
  bool *ans = ans1;
  int anscnt = ans1cnt;
  
  // Select the better solution
  for (int i = n << 1; i; --i) {
    if (ans1[i] == ans2[i]) {
      continue;
    }
    
    if (ans1[i]) {
      ans = ans2;
      anscnt = ans2cnt;
    } else {
      ans = ans1;
      anscnt = ans1cnt;
    }
    break;
  }
  
  cout << anscnt << "\n";
  for (int i = 1; i <= n << 1; ++i) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/