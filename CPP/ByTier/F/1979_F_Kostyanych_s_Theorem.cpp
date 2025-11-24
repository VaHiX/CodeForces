// Problem: CF 1979 F - Kostyanych's Theorem
// https://codeforces.com/contest/1979/problem/F

/*
Algorithm/Techniques: 
- The problem uses an interactive approach to find a Hamiltonian path in a graph.
- It works by iteratively removing vertices and building the path in reverse.
- A query "?d" tells how many vertices have degree >= d and gives the vertex with minimum degree and minimum number, along with a vertex it is not connected to.
- The process is recursive, building a path by removing vertices one by one and maintaining connectivity information.
- Time complexity: O(n^2) in worst case due to queries and operations. Space complexity: O(n) for storage of vertex connections.

*/

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <set>
#include <utility>

#define For(i, j, k) for (int i = (j); i <= (k); ++i)
#define ForD(i, j, k) for (int i = (j); i >= (k); --i)
#define int long long
using namespace std;
bool Mbe;
#define pii pair<int, int>
#define u first
#define v second
const int N = 1e5 + 5;
pii query(int d) {
  int u, v;
  cout << "? " << d << endl;
  cin >> u >> v;
  return {u, v};
}
set<int> S;
int nxt[N];
pii dfs(int n) {
  if (n <= 2) {
    if (n == 2) {
      auto I = S.begin();
      int u = *I;
      I++;
      int v = *I;
      nxt[u] = v;
      return {u, v};
    }
    return {*S.begin(), *S.begin()};
  }
  pii I = query(n - 2); // Query with degree threshold n-2
  int u = I.u, v = I.v;
  S.erase(u); // Remove u from the set of available vertices
  pii G;
  if (v) { // If vertex v is found (not 0)
    G = dfs(n - 1); // Recurse with n-1 vertices
    if (G.u == v) // If the first vertex in path is v
      nxt[G.v] = u, G.v = u; // Update next pointer
    else
      nxt[u] = G.u, G.u = u; // Update next pointer
  } else {
    // If v is 0, meaning vertex u is not connected to any other vertices
    pii _I = query(0); // Query with degree threshold 0
    int nu = _I.u;
    S.erase(nu); // Remove nu from set
    nxt[nu] = u; // Set next pointer
    G = dfs(n - 2); // Recurse with n-2 vertices
    nxt[u] = G.u, G.u = nu; // Update pointers
  }
  return G; // Return the path endpoints
}
void solve() {
  S.clear(); // Clear the set of vertices
  int n;
  cin >> n;
  For(i, 1, n) nxt[i] = 0, S.insert(i); // Initialize next pointers and add all vertices to set
  pii G = dfs(n); // Start the recursive dfs to build path
  int u = G.u; // Start from the first vertex in the path
  cout << "! ";
  while (u) { // Traverse until end of path
    cout << u << ' ';
    u = nxt[u]; // Move to next vertex
  }
  cout << endl;
}
bool Med;
signed main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _ = 1;
  cin >> _;
  while (_--)
    solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/