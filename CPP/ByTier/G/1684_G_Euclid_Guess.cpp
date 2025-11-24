// Problem: CF 1684 G - Euclid Guess
// https://codeforces.com/contest/1684/problem/G

/*
Purpose: This code attempts to reconstruct an array of pairs (a, b) such that 
         when Euclid's algorithm is applied to each pair, the resulting remainders 
         (in order of appearance) match the given array t. The algorithm uses 
         bipartite matching to find valid pair combinations.

Algorithms/Techniques:
- Bipartite Matching using DFS (Hungarian Algorithm approach)
- Greedy separation of elements into two groups based on value comparison with m/3
- Reconstruction of pairs from matched elements

Time Complexity: O(n^3), where n is the length of array t. In worst case, 
                 for each of n1 elements in first group, we perform DFS on all n2 elements.
Space Complexity: O(n^2), for storing the bipartite graph and auxiliary arrays.

*/
#include <stdio.h>
#include <iostream>

using namespace std;
const int N = 1010;
int n, m, a[N], vis[N], match[N], l[N], r[N], n1, n2; // l: large remainders, r: small remainders

// DFS-based function to find augmenting path in bipartite graph
bool dfs(int x) {
  if (vis[x])
    return 0;
  vis[x] = 1;
  for (int i = 1; i <= n2; i++) {
    // Check if current element in 'l' (large) can generate 'r' (small) through Euclidean steps
    // Conditions ensure valid pair generation and constraint satisfaction
    if ((l[x] * 2 <= m - r[i]) && (l[x] % r[i] == 0)) {
      if (match[i] == 0 || dfs(match[i])) {
        match[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    // Separate large and small elements of t into different arrays
    if (a[i] > m / 3)
      l[++n1] = a[i];
    else
      r[++n2] = a[i];
  }
  // Try to match each element in 'l' with an element in 'r'
  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n1; j++)
      vis[j] = 0; // Reset visited array for each new DFS
    if (!dfs(i)) { // If no augmenting path exists, then impossible to construct
      puts("-1\n");
      return 0;
    }
  }
  // Output the reconstructed pairs
  cout << n2 << endl;
  for (int i = 1; i <= n2; i++) {
    if (match[i] == 0)
      // No pairing; reconstruct using simple formula for unmatched small elements
      cout << 3 * r[i] << " " << 2 * r[i] << endl;
    else
      // Pairing exists; reconstruct using matched values
      cout << 2 * l[match[i]] + r[i] << " " << l[match[i]] + r[i] << endl;
  }
}


// https://github.com/VaHiX/CodeForces/