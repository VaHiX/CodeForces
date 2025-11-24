// Problem: CF 2120 C - Divine Tree
// https://codeforces.com/contest/2120/problem/C

/*
C. Divine Tree
Purpose: Construct a rooted tree with n nodes such that the sum of divineness (minimum node on path from root to node) equals m.
Algorithms/Techniques:
    - Greedy construction using optimal subtree size k.
    - Math calculation for minimal and maximal possible sums.
Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n), for storing the tree structure.

Input format:
- t test cases
- Each case: n (nodes), m (target sum of divineness)

Output:
- If impossible, print "-1"
- Else, print root node and all edges in the tree
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    ll m;
    cin >> n >> m;
    // Minimum possible sum: each node has divineness of 1 (chain tree)
    ll mn = n;
    // Maximum possible sum: root has divineness 1, all others have increasing divineness
    ll mx = 1ll * n * (n + 1) / 2;
    if (m < mn || m > mx) {
      cout << "-1\n";
      continue;
    }
    
    int k = 1;
    // Find optimal number of nodes in the "chain" part
    for (; k <= n; k++) {
      ll s = 1ll * k * (2ll * n - k + 1) / 2;  // Total divineness if root is at level k+1
      ll d = s - m;                            // Difference needed to adjust
      ll cap = 1ll * (n - k) * (k - 1);        // Maximum adjustment possible due to remaining nodes
      if (d >= 0 && d <= cap)
        break;
    }
    cout << k << "\n";
    
    vector<int> p(n + 1, 0);  // Store parent of each node
    
    // Assign all nodes from 1 to k-1 with parent k
    for (int i = 1; i < k; i++)
      p[i] = k;
    
    // Adjust divineness for remaining nodes using difference d
    ll d = 1ll * k * (2ll * n - k + 1) / 2 - m;
    for (int v = k + 1; v <= n; v++) {
      if (!d) {
        p[v] = k;
        continue;
      }
      // Reduce divineness by min(d, k-1) to match sum
      ll t = min<ll>(d, k - 1);
      p[v] = k - t;
      d -= t;
    }
    
    // Output edges
    for (int v = 1; v <= n; v++)
      if (v != k)
        cout << v << " " << p[v] << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/