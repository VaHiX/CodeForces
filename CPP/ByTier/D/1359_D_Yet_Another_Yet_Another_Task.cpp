// Problem: CF 1359 D - Yet Another Yet Another Task
// https://codeforces.com/contest/1359/problem/D

/*
D. Yet Another Yet Another Task
Algorithm: Brute Force with Sliding Window Optimization
Time Complexity: O(30 * n) = O(n)
Space Complexity: O(n)

This code solves a game problem where Alice selects a segment of cards,
and Bob removes one card from that segment to minimize the sum of remaining cards.
The goal is to maximize the final score by choosing the optimal segment.

Approach:
- For each possible maximum value (1 to 30), we simulate the process:
  - We iterate through all cards and maintain a running sum.
  - For each card, if it's <= max_val, we continue extending the subarray;
    otherwise, we reset the current sum.
  - We track the maximum difference between current sum and max_val,
    which represents the best score achievable for that max_val.

The solution leverages the constraint that a_i is bounded by [-30, 30],
so trying all values from 1 to 30 is efficient enough.
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
  ll ans(0);
  for (ll mx = 1; mx <= 30; mx++) { // Try all possible max values from 1 to 30
    ll cur(0);
    for (ll p = 0; p < n; p++) {
      cur += a[p];                    // Extend the current subarray sum
      cur = (cur > 0) ? cur : 0;      // Reset if current sum becomes negative
      cur = (a[p] <= mx) ? cur : 0;   // If card value exceeds max, reset
      ll tmp = cur - mx;              // Calculate potential score for this segment
      ans = (ans > tmp) ? ans : tmp;  // Update global maximum score
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/