// Problem: CF 1725 I - Imitating the Key Tree
// https://codeforces.com/contest/1725/problem/I

/*
 * Purpose: This code calculates the number of distinct undirected weighted graphs satisfying specific conditions
 *          related to a key tree and edge weight assignments.
 * 
 * Algorithm/Techniques:
 * - Union-Find (Disjoint Set Union) for managing connected components
 * - Counting valid edge weight assignments using combinatorial logic
 * - Modular arithmetic to handle large numbers and prevent overflow
 * 
 * Time Complexity: O(N * α(N)) where α(N) is the inverse Ackermann function (practically constant)
 * Space Complexity: O(N) for storing parent and size arrays
 * 
 * Key Idea:
 * - The number of valid graphs is computed based on:
 *   1. The number of ways to assign weights to the edges of the key tree (in increasing order).
 *   2. For each edge added in the union process, the number of valid assignments depends on the sizes of the components.
 * 
 * The final result is calculated as a product of terms related to component sizes during union operations.
 */

#include <iostream>
using namespace std;
const int mod = 998244353;
int fa[100010], sz[100010];

// Find function with path compression
int getF(int x) { return fa[x] == x ? x : fa[x] = getF(fa[x]); }

int main() {
  int n, u, v, ans = 1;
  cin >> n;
  
  // Precompute the product of odd numbers from 3 to 2*N - 3
  // This part contributes to the combinatorial count of valid edge weight assignments
  for (int i = 3; i <= 2 * n - 3; i += 2)
    ans = (long long)ans * i % mod;
  
  // Initialize Union-Find structure
  for (int i = 1; i <= n; i++)
    fa[i] = i, sz[i] = 1;
  
  // Process each edge of the tree and compute contribution to answer
  for (int i = 1; i < n; i++) {
    cin >> u >> v;
    u = getF(u);
    v = getF(v);
    
    // Calculate the weight multiplier for current edge
    long long w = (long long)sz[u] * sz[v] % mod;
    
    // Union operation: merge components
    fa[u] = v;
    sz[v] += sz[u];
    
    // Multiply the answer by (w * w) for the current edge
    ans = ans * w % mod * w % mod;
  }
  
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/