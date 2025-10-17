// Problem: CF 2053 F - Earnest Matrix Complement
// https://codeforces.com/contest/2053/problem/F

/*
F. Earnest Matrix Complement
Algorithm/Techniques: Dynamic Programming with Segment Tree / Fenwick Tree, Greedy Optimization
Time Complexity: O(n * m + k * n)
Space Complexity: O(n * m + k)

This code solves a problem where we need to maximize the beauty of a matrix A of size n x m,
where each cell is filled with an integer from [1, k]. Some cells are pre-filled, others are -1.
The beauty is computed as sum over all pairs of adjacent rows (i and i+1) of products of counts
of each value u in those two rows. The optimization uses a data structure to efficiently manage
updates and queries while computing the best possible assignment of values to fill -1 cells.

We precompute common counts, then use a dynamic programming approach that maintains
an optimal cost for assigning values to current row based on previous row's assignments.
*/

#include <algorithm>
#include <iostream>
#include <string>

#define ll long long
#define vector basic_string
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 2e5 + 5, M = 6e5 + 5;
int _, n, m, k, x, c[M];
ll ans;
vector<int> a[N];

struct DS {
  ll f[M], ad, mx, an;
  
  // Reset all state variables for new test case
  inline void clr() {
    ad = mx = an = 0;
    for (int i = 1; i <= k; i++)
      f[i] = 0;
  }
  
  // Adds value v to ad, mx and an - for global increment tracking
  inline void Add(ll v) { ad += v, mx += v, an += v; }
  
  // Update max of mx and an with v
  inline void Max(ll v) { mx = max(mx, v), an = max(an, v); }
  
  // Add contribution of value x to the state with given offset
  inline void add(int x, ll v) {
    an = max(an, f[x] = max(f[x] + ad, mx) + v), f[x] -= ad;
  }
} S;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  cin >> _;
  
  while (_--) {
    cin >> n >> m >> k;
    ans = 0;
    
    // Read input matrix, store non-negative values in a vector
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (cin >> x, ~x) // If x is not -1
          a[i].pb(x);
    
    // Precompute overlap count between first and second row
    for (int i = 1; i < n; i++) {
      for (int j : a[i])
        c[j]++; // Count occurrences in current row
      for (int j : a[i + 1])
        ans += c[j]; // Add to total if present in next row
      for (int j : a[i])
        c[j] = 0; // Reset counts after computation
    }
    
    S.clr(); // Clear DS struct before using
    
    // Initialize with second row values
    for (int i : a[2])
      S.add(i, m - SZ(a[1]));
      
    for (int i = 2; i <= n; i++) {
      int x = S.an; // Current optimal result before processing this row
      int e = m - SZ(a[i]); // Unfilled entries in current row
      
      // Apply update due to row transition cost
      S.Add(1ll * e * (m - SZ(a[i - 1])));
      
      // Maximize against previous max
      S.Max(x);
      
      // Update each element of previous row with new transitions
      for (int j : a[i - 1])
        S.add(j, e);
        
      if (i < n)
        // Add contribution from next row if exists
        for (int j : a[i + 1])
          S.add(j, e);
    }
    
    cout << S.an + ans << '\n';
    
    // Clear current row data for next iteration
    for (int i = 1; i <= n; i++)
      a[i].clear();
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/