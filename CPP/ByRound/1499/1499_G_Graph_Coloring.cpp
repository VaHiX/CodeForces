// Problem: CF 1499 G - Graph Coloring
// https://codeforces.com/contest/1499/problem/G

/*
 * Problem: Graph Coloring on Bipartite Graph
 *
 * Algorithms/Techniques:
 * - Union-Find (Disjoint Set Union) with path compression and color tracking
 * - Online edge addition with dynamic coloring
 * - Hash computation with modular arithmetic
 *
 * Time Complexity: O((n1 + n2 + m + q) * α(n1 + n2 + m)) where α is inverse
 * Ackermann function Space Complexity: O(n1 + n2 + m)
 *
 * Approach:
 * - Use Union-Find to maintain connected components
 * - Track colors of edges (0 or 1) using XOR trick for efficient updates
 * - Maintain sum of red/blue edges in each component for minimizing cost
 * - Each query adds an edge and computes optimal assignment, then outputs hash
 * - For query type 2, reconstruct the coloring from stored state
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = b; a <= i; i--)
#define ll long long
#define fi first
#define se second
using namespace std;
const int N = 444000;
const int P = 998244353;
int n1, n2, w = 1, m, q, sum[N][2], fa[N], id[N], col[N], cnt;
ll ans;
int find(int x) {
  // Find root with path compression and color propagation
  if (fa[x] == x)
    return x;
  int p = find(fa[x]);
  col[x] ^= col[fa[x]]; // XOR to compute color difference
  return fa[x] = p;
}
void merge(int x, int y) {
  // Merge two components
  int px = find(x), py = find(y), d = col[x] ^ col[y] ^ 1;
  if (px == py)
    return;
  // If color mismatch, flip color of one component
  if (d == 1) {
    ans = (ans - sum[px][1] + sum[px][0] + P) % P;
    swap(sum[px][0], sum[px][1]);
    col[px] = 1;
  }
  fa[px] = py;
  // Update sum of edges in merged component
  sum[py][0] = (sum[py][0] + sum[px][0]) % P;
  sum[py][1] = (sum[py][1] + sum[px][1]) % P;
}
void add() {
  // Add a new edge to the graph
  int a, b;
  cin >> a >> b;
  b += n1;         // Convert second part index to global index
  w = (2 * w) % P; // Update weight for hash calculation
  sum[++cnt][0] = w;
  fa[cnt] = cnt;
  // Ensure smaller index comes first for consistency
  if (id[a] > id[b])
    swap(a, b);
  // Handle different cases of existing connections
  if (!id[a] && !id[b])
    id[a] = id[b] = cnt;
  else if (!id[a]) {
    merge(id[b], cnt);
    id[a] = cnt;
    id[b] = 0;
  } else {
    merge(id[a], cnt);
    merge(id[b], cnt);
    id[a] = id[b] = 0;
  }
}
int main() {
  cin >> n1 >> n2 >> m;
  // Initialize with existing edges
  while (m--)
    add();
  cin >> q;
  // Process queries one by one
  while (q--) {
    int e;
    cin >> e;
    if (e == 1)
      add(), cout << ans << endl;
    else {
      // For query type 2, output the coloring
      vector<int> ans_vec;
      rep(i, 1, cnt) {
        find(i);
        if (col[i]) // If edge is red (col=1)
          ans_vec.push_back(i);
      }
      cout << ans_vec.size() << endl;
      for (auto x : ans_vec)
        cout << x << " ";
      cout << endl;
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/