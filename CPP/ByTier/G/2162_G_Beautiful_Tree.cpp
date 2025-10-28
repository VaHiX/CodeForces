// Problem: CF 2162 G - Beautiful Tree
// https://codeforces.com/contest/2162/problem/G

/*
Purpose: 
This code solves the "Beautiful Tree" problem, where we need to construct a tree with n vertices such that the sum of products of vertex labels for all edges is a perfect square. 

Algorithm:
- For small values of n (n < 10), specific constructions are used based on precomputed solutions.
- For larger values of n, a general construction strategy is used:
  - Connect all vertices from 3 to n-4 to vertex 2.
  - Connect vertices n-3 and n-4 to vertex 1.
  - This ensures that the sum of products forms a perfect square.

Time Complexity: O(n) per test case
Space Complexity: O(1) - only using a constant amount of extra space (excluding input/output)

Techniques:
- Precomputed cases for small n
- Constructive algorithm for larger n
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int MAXN = 2e5 + 10;
int n, m;

// This function seems unused in the current implementation, but may be for testing permutations
void check(int n) {
  vector<int> a(n);
  for (int i = 0; i < n; ++i)
    a[i] = i;
  while (next_permutation(a.begin(), a.end())) {
    for (int i = 0; i < n; ++i) {
    }
  }
}

// Main solution function
void sol() {
  cin >> n;
  if (n < 10) {
    // Handle small cases with predefined solutions
    if (n == 2) {
      cout << -1 << '\n';  // No beautiful tree exists for 2 vertices
    } else if (n == 3) {
      cout << "1 3\n2 3\n";  // Example from problem description
    } else if (n == 4) {
      cout << "1 2\n3 1\n4 1\n";  // Example from problem description
    } else if (n == 5) {
      cout << "2 5\n3 5\n4 5\n1 4\n";  // Constructed solution
    } else if (n == 6) {
      cout << "1 6\n5 6\n 2 5\n3 5\n4 5\n";  // Constructed solution
    } else if (n == 7) {
      cout << "1 7\n2 7\n3 6\n4 7\n5 7\n6 7\n";  // Constructed solution
    } else if (n == 8) {
      cout << "1 8\n2 8\n3 8\n4 1\n5 8\n6 8\n7 8\n";  // Constructed solution
    } else if (n == 9) {
      cout << "1 9\n2 9\n3 9\n4 9\n 5 9\n6 9\n7 9\n8 9\n";  // Constructed solution
    }
    return;
  }
  
  // For n >= 10, use general strategy:
  // Connect all vertices to 2 except for vertex 2 itself and special cases
  for (int i = 1; i <= n; ++i) {
    if (i == 2)
      continue;  // Skip connecting vertex 2 to itself
    if (i == n - 4)
      cout << i << " 1\n";  // Special handling for last few vertices
    else
      cout << i << " 2\n";  // Connect others to vertex 2
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    sol();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/