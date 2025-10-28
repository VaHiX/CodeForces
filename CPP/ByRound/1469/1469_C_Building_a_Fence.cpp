// Problem: CF 1469 C - Building a Fence
// https://codeforces.com/contest/1469/problem/C

#include <algorithm>
#include <cstdio>
typedef long long ll;

/*
 * Problem: C. Building a Fence
 *
 * Purpose:
 *   Determine if it's possible to build a fence with n sections, each of height k,
 *   such that consecutive sections share at least 1 unit of common side, the first
 *   and last sections are placed on their respective ground levels h_i, and internal
 *   sections can be placed at heights between ground level and ground + k - 1 (inclusive).
 *
 * Algorithm:
 *   Greedy approach. For each section from left to right:
 *     - Maintain a range [lower, upper] of valid heights for the current section.
 *     - The lower bound is updated as max(lower - k + 1, x) meaning it can drop at most k-1
 *       from previous height but must stay at least x (current ground level).
 *     - The upper bound is updated as min(upper + k - 1, x + k - 1) because it can rise at most k-1.
 *     - If the range becomes invalid (upper < x or lower > x + k - 1), impossible.
 *     - At end, check that final section matches its ground level exactly.
 *
 * Time Complexity: O(n) per test case. Each element processed once.
 * Space Complexity: O(1). Only constant extra space used.
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll x;
    scanf("%lld", &x);
    ll lower(x), upper(x);       // Initialize bounds to ground level of first section
    bool possible(true);
    for (long p = 1; p < n; p++) {  // Process remaining sections
      scanf("%lld", &x);
      // Update the valid range for current section based on previous valid range
      lower = std::max(lower - k + 1, x);
      upper = std::min(upper + k - 1, x + k - 1);
      // Check if the range is still valid (i.e., we can fit this section's ground)
      if (upper < x || lower > x + k - 1) {
        possible = false;
      }
    }
    // Final check: last section must exactly match its ground level
    if (lower != x) {
      possible = false;
    }
    puts(possible ? "YES" : "NO");
  }
}

// https://github.com/VaHiX/codeForces/