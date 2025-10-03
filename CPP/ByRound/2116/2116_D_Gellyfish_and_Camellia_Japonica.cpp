// Problem: CF 2116 D - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2116/problem/D

/*
D. Gellyfish and Camellia Japonica
Algorithms/Techniques: Graph processing, Union-find or dependency tracking
Time Complexity: O(n + q)
Space Complexity: O(n + q)

Task:
Given final array b after q operations where each operation sets c[z_i] = min(c[x_i], c[y_i]),
find an initial array a such that applying the operations results in b.
If impossible, output -1.

Operations are processed backwards to determine constraints on original values,
then forward pass ensures consistency with the original rules.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1); // a is original array, b is final result
    for (int i = 1; i <= n; i++) {
      cin >> a[i], b[i] = a[i]; // Read input and store it in b
    }
    vector<int> x(q + 1), y(q + 1), z(q + 1);
    for (int i = 1; i <= q; i++) {
      cin >> x[i] >> y[i] >> z[i]; // Read operations
    }
    
    // Process operations backwards to reconstruct possible values
    for (int i = q; i >= 1; i--) {
      a[x[i]] = max(a[x[i]], a[z[i]]); // Ensure x[i] is at least as big as z[i]
      a[y[i]] = max(a[y[i]], a[z[i]]); // Same for y[i]
      if (x[i] != z[i] && y[i] != z[i])
        a[z[i]] = 0; // If both x and y are different from z, set z to 0
    }
    
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++)
      c[i] = a[i]; // Save reconstructed values
    
    // Forward pass to enforce constraints from operations
    for (int i = 1; i <= q; i++) {
      a[z[i]] = min(a[x[i]], a[y[i]]); // Apply the operation in forward direction
    }
    
    bool fl = true;
    // Check equivalence with original values
    for (int i = 1; i <= n; i++)
      fl = fl && (a[i] == b[i]);
      
    if (!fl)
      cout << -1; // No valid solution exists
    else
      for (int i = 1; i <= n; i++)
        cout << c[i] << " "; // Output valid solution
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/