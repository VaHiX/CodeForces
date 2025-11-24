// Problem: CF 1894 E - Freedom of Choice
// https://codeforces.com/contest/1894/problem/E

/*
Code Purpose:
This code solves the "Freedom of Choice" problem where we need to minimize the anti-beauty of a multiset X formed by selecting elements from multiple multisets. The anti-beauty is defined as the number of occurrences of the size of the multiset in the multiset itself.

Algorithms/Techniques:
- Binary search or direct computation approach for minimizing anti-beauty
- Prefix sum and greedy selection from multisets
- Optimization using range-based selection and tracking of element counts

Time Complexity: O(sum of n_i) where sum of n_i is bounded by 1e5
Space Complexity: O(R - L) where R - L can be up to 2e17 but capped at 1e5 for efficiency
*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

void solve() {
  int m;
  cin >> m;
  ll L = 0;
  ll R = 0;
  vector<ll> n(m), l(m), r(m);
  vector<vector<ll>> a(m), c(m);
  for (int i = 0; i < m; i++) {
    cin >> n[i] >> l[i] >> r[i];
    R = min(R + r[i], (ll)2e17); // Update upper bound of total selected elements
    L = min(L + l[i], (ll)2e17); // Update lower bound of total selected elements
    a[i] = vector<ll>(n[i]);
    c[i] = vector<ll>(n[i]);
    for (int j = 0; j < n[i]; j++)
      cin >> a[i][j];
    for (int j = 0; j < n[i]; j++)
      cin >> c[i][j];
  }
  
  // Early termination if range is too large to handle efficiently
  if (R - L + 1 > 1e5 || R > 1e17) {
    cout << "0\n";
    return;
  }
  
  // Mark which positions in the range [L, R] are covered by any element
  vector<bool> e(R - L + 1);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n[i]; j++)
      if (L <= a[i][j] && a[i][j] <= R)
        e[a[i][j] - L] = true; // Mark that this element appears in range
  }
  
  int cnt = 0;
  for (int i = 0; i < R - L + 1; i++)
    cnt += e[i]; // Count how many distinct values in [L,R] actually exist
	
  // If more elements in range than distinct values, then anti-beauty can be 0
  if (R - L + 1 > cnt) {
    cout << "0\n";
    return;
  }
  
  vector<ll> res(R - L + 1);   // How many extra times each element appears
  vector<ll> sub(R - L + 1);   // How many times each element can be subtracted
  ll oc = 0;  // Total number of elements selected from all multisets
  
  // Process each multiset
  for (int i = 0; i < m; i++) {
    ll s = 0;
    // Compute prefix sum of counts to help determine how much can be taken
    for (int j = 0; j < n[i]; j++)
      s = min(s + c[i][j], (ll)3e17);
    
    for (int j = 0; j < n[i]; j++) {
      if (L <= a[i][j] && a[i][j] <= R) { // Check if element is within our range
        ll left = s - c[i][j]; // Amount left after taking 'c[i][j]' copies from this element
        if (left < l[i]) { // Not enough to meet minimum requirement
          // Calculate how many we must use to reach 'l[i]'
          res[a[i][j] - L] += l[i] - left;
          // Update sub based on the maximum we could have used
          sub[a[i][j] - L] += r[i] - min(left, r[i] - (l[i] - left));
        } else {
          // Even if we take minimum, we're good
          sub[a[i][j] - L] += r[i] - min(left, r[i]);
        }
      }
    }
    oc += r[i]; // Track total selected up to this point
  }
  
  ll ans = 2e18;
  // Find the minimum anti-beauty by trying all possible sizes
  for (int i = 0; i < R - L + 1; i++) {
    // res[i] is how many extra we used, so actual count = i + res[i] (index i corresponds to L+i)
    // We're trying to minimize: (count of L+i in X) + (number of non-L+i elements in X)
    ans = min(ans, res[i] + max(L + i - res[i] - (oc - sub[i]), 0ll));
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  for (int i = 0; i < t; i++)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/