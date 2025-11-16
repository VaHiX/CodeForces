// Problem: CF 1760 F - Quests
// https://codeforces.com/contest/1760/problem/F

/*
 * Problem: F. Quests
 * Algorithm: Binary search on answer with prefix sums for optimization
 * Time Complexity: O(n log n + t * log d * log n) where t is number of test cases, n is number of quests
 * Space Complexity: O(n)
 *
 * Approach:
 * 1. Sort quests in descending order to prioritize higher value quests.
 * 2. Precompute prefix sums for efficient range sum queries.
 * 3. Binary search on the possible value of k (cooldown period).
 * 4. For a given k, compute maximum coins achievable over d days:
 *    - Calculate how many full cycles of k days we can do
 *    - Handle partial cycle at the end
 *    - Use prefix sums to quickly compute total coins for selected quests.
 * 5. Edge cases:
 *    - If even the best possible value (k = d) is insufficient, return "Impossible"
 *    - If c <= sum of first d quests (or full n), return "Infinity"
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, c, d;
    scanf("%lld %lld %lld", &n, &c, &d);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order to select highest values first
    
    std::vector<ll> cs(n + 1, 0); // Prefix sum array for quick range sum calculation
    for (ll p = 1; p <= n; p++) {
      cs[p] = cs[p - 1] + a[p - 1];
    }
    
    // Early exit: if even after doing the best quest every day is not enough, impossible
    if (d * a[0] < c) {
      puts("Impossible");
      continue;
    }
    
    // Early exit: if we can do enough in first d days regardless of delay, infinity
    if (c <= cs[d < n ? d : n]) {
      puts("Infinity");
      continue;
    }
    
    ll res(0), left(1), right(d); // Binary search bounds for k
    
    while (left <= right) {
      ll mid = (left + right) / 2; // Current candidate k value
      
      ll stopA = (mid <= n) ? mid : n;  // Number of unique quests we can take in one cycle
      ll stopB = (d % mid <= n) ? (d % mid) : n;  // Remaining quests after full cycles
      
      ll sum = (d / mid) * cs[stopA] + cs[stopB];  // Total coins achievable with cooldown of 'mid'
      
      if (c <= sum) {
        res = mid;     // This k works, try larger
        left = mid + 1;
      } else {
        right = mid - 1; // This k doesn't work, try smaller
      }
    }
    
    printf("%lld\n", res - 1); // Result is actually k-1 since we subtracted one due to iteration detail
  }
}


// https://github.com/VaHiX/codeForces/