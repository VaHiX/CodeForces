// Problem: CF 2024 B - Buying Lemonade
// https://codeforces.com/contest/2024/problem/B

/*
Problem: Buying Lemonade
Purpose: Determine the minimum number of button presses needed to guarantee at least k cans of lemonade,
         given that the slots are unlabeled and we do not know which button corresponds to which slot.

Algorithms/Techniques:
- Greedy strategy with sorting
- Binary search or simulation approach to minimize total presses by selecting optimal sequence

Time Complexity: O(n log n) per test case due to sorting; overall O(n log n) for all test cases.
Space Complexity: O(n) for storing the vector of cans.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort to process from smallest to largest pile
    
    ll cnt(0), prev(0);
    for (ll p = 0; p < n; p++) {
      ll diff = v[p] - prev; // Difference between current and previous pile size
      prev = v[p];
      
      ll num = diff * (n - p); // Total number of cans we could get if all remaining slots had this difference
      
      if (k <= num) {
        // If we need fewer cans than what's available, just add k presses
        cnt += k;
        break;
      } else {
        // Otherwise, press all slots for this difference and adjust remaining k
        cnt += num + 1; // Add one more because pressing the slot gives a can (so total = diff * (n-p) + 1)
        k -= num;
      }
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/