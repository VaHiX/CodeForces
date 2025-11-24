// Problem: CF 2064 C - Remove the Ends
// https://codeforces.com/contest/2064/problem/C

/*
C. Remove the Ends
Problem Description:
Given an array of non-zero integers, we play a game where at each step,
we pick an element from either end of the array and gain coins equal to its absolute value.
If the picked element is negative, we remove everything from that point onwards.
If positive, we remove everything up to that point.
Goal: Find the maximum number of coins possible.

Algorithm:
Dynamic Programming with preprocessing of alternating signs.
We split the array into segments where each segment has either all positive or all negative numbers,
and then use DP to compute maximum coins by choosing optimal ends of segments.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing segments

This problem is solved using:
- Segment grouping based on sign changes
- Dynamic programming with forward and backward passes
- Greedy-like selection for maximum profit accumulation
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v; // Stores sums of contiguous same-sign segments
    ll cs(0); // Current sum of a segment
    
    // Group array elements into contiguous segments with same sign
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      if ((cs >= 0 && x > 0) || (cs <= 0 && x < 0)) {
        // Continue current segment with same sign
        cs += x;
      } else {
        // End previous segment and start new one
        v.push_back(cs);
        cs = x;
      }
    }
    v.push_back(cs); // Push last segment

    // Forward pass: accumulate from left to right
    // Combine every other segment to maximize gain
    for (ll p = 0; p < v.size(); p++) {
      if (v[p] < 0) {
        continue; // Skip negative segments
      }
      // Add the value of 2 steps back to current segment (if exists)
      v[p] += (p >= 2 ? v[p - 2] : 0);
    }

    // Backward pass: accumulate from right to left
    // Similar to forward, but going backwards
    for (ll p = v.size() - 1; p >= 0; p--) {
      if (v[p] > 0) {
        continue; // Skip positive segments in backward pass
      }
      // Add the value of 2 steps forward to current segment (if exists)
      v[p] += (p + 2 < v.size() ? v[p + 2] : 0);
    }

    // Final calculation to find optimal choice at each step
    ll ans(0);
    for (ll p = 0; p < v.size(); p++) {
      ll tst(0);
      if (v[p] > 0) {
        // For positive segments, compare with next segment
        tst = v[p] - (p + 1 < v.size() ? v[p + 1] : 0);
      } else {
        // For negative segments, compare with previous segment
        tst = -v[p] + (p ? v[p - 1] : 0);
      }
      ans = (ans > tst ? ans : tst); // Keep maximum profit
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/