// Problem: CF 2051 E - Best Price
// https://codeforces.com/contest/2051/problem/E

/*
E. Best Price

Algorithms/Techniques: Sweep Line + Sorting + Two Pointers

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing customer data

The problem involves setting an optimal price for Christmas trees such that the total revenue is maximized,
while limiting the number of negative reviews to at most k.

Approach:
- Each customer has two thresholds: a_i (positive review) and b_i (negative review).
- We use a sweep line technique by creating events for all a_i and b_i values.
- For each valid price point (where we can still have ≤k negative reviews), we compute the revenue.
- The key insight is that we want to place the price such that we maximize (number of customers who buy) * (price),
  where the number of customers who buy depends on how many are in [0, price] range.

This solution sorts all customer thresholds and sweeps through them, keeping track of current counts of
customers who could buy with a positive review vs negative review.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define int long long
#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0)

void solve() {
  int n, k, t;
  cin >> n >> k;
  vector<pair<int, int>> v; // {price_threshold, type} where type=0 (a_i), type=1 (b_i)
  for (int i = 0; i < n; i++) {
    cin >> t;
    v.push_back({t, 0}); // a_i values
  }
  for (int i = 0; i < n; i++) {
    cin >> t;
    v.push_back({t, 1}); // b_i values
  }
  
  sort(v.begin(), v.end()); // Sort by threshold value
  
  int ans = 0, c0 = n, c1 = 0, lst = 0; // c0: count of customers with a_i >= price, c1: count of with b_i >= price
  for (auto tt : v) {
    int x = tt.first, y = tt.second;
    // If the current threshold is > last valid price AND we can still have <= k negative reviews,
    // compute possible revenue at this point
    if (x > lst && c1 <= k)
      ans = max(ans, x * (c0 + c1));
    lst = x; // Update last processed threshold
    if (y == 0) {
      c0--; // Customer who buys with positive review no longer qualifies for that category
      c1++; // Customer now eligible for negative review category
    } else
      c1--; // Customer leaves negative review category
  }
  cout << ans << endl;
}

signed main() {
  IOS;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/