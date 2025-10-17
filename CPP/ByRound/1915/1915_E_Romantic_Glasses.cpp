// Problem: CF 1915 E - Romantic Glasses
// https://codeforces.com/contest/1915/problem/E

/*
E. Romantic Glasses
Algorithm: Prefix Sums with Set
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem asks to find a contiguous subarray where the sum of elements at odd indices 
equals the sum of elements at even indices (within that subarray), or vice versa, 
depending on whether the starting index is odd or even.

Approach:
1. Modify the array such that all elements at odd indices are negated.
   This allows us to reframe the problem into finding a subarray with sum 0.
2. Use prefix sums to track cumulative sums.
3. If we encounter a repeated prefix sum, it indicates a subarray with sum 0 exists.

Key insights:
- By negating odd-indexed elements, the original problem becomes searching for a zero-sum subarray.
- A zero sum implies equal contributions from both Iulia and her date.
- We use a set to store previously seen prefix sums for efficient lookup.

*/

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      if (p % 2) {           // If index is odd, negate the value
        v[p] = -v[p];
      }
    }
    ll cs(0);                // Cumulative sum
    bool ans(false);         // Result flag
    std::set<ll> w;          // Set to store prefix sums
    w.insert(0);             // Initialize with 0 to handle subarrays starting from index 0
    
    for (ll p = 0; !ans && p < n; p++) {
      cs += v[p];            // Update cumulative sum
      if (w.count(cs)) {     // If this sum was seen before, a zero-sum subarray exists
        ans = true;
      }
      w.insert(cs);          // Insert current prefix sum
    }
    
    puts(ans ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/