// Problem: CF 771 A - Bear and Friendship Condition
// https://codeforces.com/contest/771/problem/A

/*
 * Problem: Bear and Friendship Condition
 * Algorithm/Techniques: Disjoint Set Union (DSU), Graph Theory, Complete Graph Check
 * 
 * Time Complexity: O(m * α(n) + n) where α is the inverse Ackermann function, nearly constant
 * Space Complexity: O(n + m) for adjacency list and DSU structures
 * 
 * The solution checks if a social network is "reasonable" - meaning that for any three members,
 * if member A is friends with B and B is friends with C, then A must also be friends with C.
 * This is equivalent to checking whether every connected component in the graph is a complete graph.
 * 
 * Approach:
 * 1. Use DSU to identify connected components.
 * 2. For each component, calculate the number of edges and compare it with the expected number
 *    of edges in a complete graph with the same number of vertices.
 * 3. If all components satisfy the condition, the network is reasonable.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 150010
#define inf 1000000000
#define pp pair<int, int>
using namespace std;

class DisjointSetUnion {
  int n;
  int *p, *r;

public:
  DisjointSetUnion(int n) {
    this->n = n;
    p = new int[n + 1];
    r = new int[n + 1];
    for (int i = 0; i <= n; i++)
      r[i] = 1, p[i] = i;
  }
  void Union(int a, int b) {
    int x = Find(a);
    int y = Find(b);
    if (r[x] > r[y]) {
      p[y] = x;
      r[x] += r[y];
    } else {
      p[x] = y;
      r[y] += r[x];
    }
  }
  int Find(int x) {
    if (p[x] == x)
      return x;
    return p[x] = Find(p[x]); // Path compression
  }
};

vector<int> adj[N]; // Adjacency list for the graph
vector<int> st[N];  // Stores vertices of each connected component

int main() {
  int i, j, k;
  int n, m;
  int u, v;
  ll x, y;
  scanf("%d%d", &n, &m);
  DisjointSetUnion dsu(n);
  
  // Read edges and build the graph
  for (i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    dsu.Union(u, v); // Union the two vertices
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  // Group vertices by their root in DSU (i.e., group by connected components)
  for (i = 1; i <= n; i++) {
    k = dsu.Find(i);
    st[k].push_back(i);
  }
  
  // Check each connected component
  for (i = 1; i <= n; i++) {
    if (st[i].size() > 0) {
      x = 0;
      // Count total degree in the component (we count each edge twice)
      for (j = 0; j < st[i].size(); j++)
        x += adj[st[i][j]].size();
      x /= 2; // Divide by two to get actual number of edges
      
      y = st[i].size(); // Number of vertices in component
      // Expected number of edges in complete graph with y vertices
      y = y * (y - 1) / 2;
      
      // If actual edges != expected edges, not a complete graph
      if (x == y)
        continue;
      else {
        printf("NO\n");
        return 0;
      }
    }
  }
  
  printf("YES\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/