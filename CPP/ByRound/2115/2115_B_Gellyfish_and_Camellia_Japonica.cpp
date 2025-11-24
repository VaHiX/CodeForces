// Problem: CF 2115 B - Gellyfish and Camellia Japonica
// https://codeforces.com/contest/2115/problem/B

/*
B. Gellyfish and Camellia Japonica

Purpose:
This code determines if there exists a valid initial array `a` such that after applying a sequence of `q` operations,
the final array becomes equal to the given array `b`. Each operation modifies elements by setting `c[z[i]] = min(c[x[i]], c[y[i]])`.

Algorithms/Techniques:
- Reverse simulation of operations
- Union-find or dependency tracking (not explicitly implemented here but assumed logically)
- Backward propagation and validation

Time Complexity: O(n + q)
Space Complexity: O(n)

The solution works by simulating the process backward:
1. It first initializes an array `a` to match the final values `b`
2. Then it reverses each modification in reverse order
3. After reversing, it validates if the resulting configuration matches the original constraints

*/
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 3e5 + 5;
int n, q, a[N], b[N], c[N];
int x[N], y[N], z[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
      a[i] = b[i]; // Initialize array a with final values b
    }
    for (int i = 1; i <= q; i++)
      cin >> x[i] >> y[i] >> z[i]; // Read the operations
    for (int i = q; i >= 1; i--) {
      // Reverse operation: Update a[x[i]] and a[y[i]] as max of themselves with a[z[i]]
      a[x[i]] = max(a[x[i]], a[z[i]]);
      a[y[i]] = max(a[y[i]], a[z[i]]);
      // Set z[i] to 0 if x[i] and y[i] are different from z[i]
      if (y[i] != z[i] && x[i] != z[i])
        a[z[i]] = 0;
    }
    for (int i = 1; i <= n; i++)
      c[i] = a[i]; // Save the intermediate result
    for (int i = 1; i <= q; i++)
      a[z[i]] = min(a[x[i]], a[y[i]]); // Apply operations forward again to validate
    bool fg = 1;
    for (int i = 1; i <= n; i++)
      fg &= (a[i] == b[i]); // Check if result matches original final state
    if (!fg) {
      cout << -1 << endl; // No valid initial array exists
    } else {
      for (int i = 1; i <= n; i++)
        cout << c[i] << ' '; // Output solution
      cout << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/