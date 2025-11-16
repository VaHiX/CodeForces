// Problem: CF 847 H - Load Testing
// https://codeforces.com/contest/847/problem/H

/*
Algorithm: Dynamic Programming + Greedy
Approach:
- We need to find the minimum number of requests to add such that the sequence becomes strictly increasing followed by strictly decreasing.
- Precompute:
  * lv[i]: the minimum value at position i to maintain a strictly increasing sequence from left to right up to i
  * lc[i]: the total number of requests needed to make the prefix [0..i] strictly increasing
  * rv[i]: the minimum value at position i to maintain a strictly decreasing sequence from right to left starting from i
  * rc[i]: the total number of requests needed to make the suffix [i..n-1] strictly decreasing
- For each possible peak position i:
  * Calculate the minimal value at i such that it's greater than both left and right neighbors
  * Compute the cost to achieve that value at i
  * Add the necessary cost from left and right parts
- Time Complexity: O(n)
- Space Complexity: O(n)

*/
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::vector<ll> a(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  // lv[i] stores the minimum value of a[i] to maintain increasing sequence from left
  std::vector<ll> lv(n, 0), rv(n, 0), lc(n, 0), rc(n, 0);
  // Initialize left part
  lv[0] = a[0], lc[0] = 0;
  for (ll p = 1; p < n; p++) {
    // Ensure strictly increasing: lv[p] must be at least lv[p-1] + 1
    lv[p] = lv[p - 1] + 1;
    // But it cannot be less than original value a[p]
    lv[p] = (lv[p] > a[p]) ? lv[p] : a[p];
    // Accumulate the number of requests needed to make prefix up to p increasing
    lc[p] = lc[p - 1] + (lv[p] - a[p]);
  }
  // Initialize right part
  rv[n - 1] = a[n - 1], rc[n - 1] = 0;
  for (ll p = n - 2; p >= 0; p--) {
    // Ensure strictly decreasing: rv[p] must be at least rv[p+1] + 1
    rv[p] = rv[p + 1] + 1;
    // But it cannot be less than original value a[p]
    rv[p] = (rv[p] > a[p]) ? rv[p] : a[p];
    // Accumulate the number of requests needed to make suffix starting from p decreasing
    rc[p] = rc[p + 1] + (rv[p] - a[p]);
  }
  ll minCost(2e18);
  // Try all positions as the peak
  for (ll p = 0; p < n; p++) {
    ll cur = a[p];
    // Ensure the peak is strictly greater than previous element
    if (p > 0 && cur <= lv[p - 1]) {
      cur = lv[p - 1] + 1;
    }
    // Ensure the peak is strictly greater than next element
    if (p + 1 < n && cur <= rv[p + 1]) {
      cur = rv[p + 1] + 1;
    }
    // Calculate cost to make current element equal to cur
    ll cost = cur - a[p];
    // Add cost of left part to make it strictly increasing
    if (p > 0) {
      cost += lc[p - 1];
    }
    // Add cost of right part to make it strictly decreasing
    if (p + 1 < n) {
      cost += rc[p + 1];
    }
    // Update minimum cost
    minCost = (minCost < cost) ? minCost : cost;
  }
  printf("%lld\n", minCost);
  return 0;
}


// https://github.com/VaHiX/CodeForces/