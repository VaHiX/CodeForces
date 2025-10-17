// Problem: CF 1995 B1 - Bouquet (Easy Version)
// https://codeforces.com/contest/1995/problem/B1

/*
B1. Bouquet (Easy Version)
Algorithm: Sliding Window
Time Complexity: O(n log n) per test case due to sorting; overall O(n log n) for all test cases combined
Space Complexity: O(n) for storing the vector of flowers

This problem asks us to select a subset of flowers such that:
1. The difference in petals between any two selected flowers is at most 1.
2. The total cost (sum of petals) does not exceed m.
3. We want to maximize the total number of petals.

Approach:
- Sort flowers by petal count.
- Use sliding window technique with two pointers:
  - Left pointer marks the start of current valid window.
  - Right pointer expands the window.
  - Maintain sum of elements in window (cur).
  - Adjust left pointer when:
    - The difference between v[left] and v[p] exceeds 1 (v[left] + 1 < v[p]).
    - The total sum exceeds m.
- Keep track of maximum sum encountered (`mx`).

Key Observations:
- Since we are sorting, all flowers in a valid window have petal counts within [x, x+1].
- We use two nested while loops to maintain the constraints.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
    }
    sort(v.begin(), v.end()); // Sort flowers by petal count
    ll left(0), cur(0), mx(0);
    for (ll p = 0; p < n; p++) {
      cur += v[p]; // Add current element to window sum
      while (v[left] + 1 < v[p]) { // Shrink window if difference > 1
        cur -= v[left++];
      }
      while (cur > m) { // Shrink window if sum exceeds budget
        cur -= v[left++];
      }
      mx = (mx > cur ? mx : cur); // Update maximum sum found so far
    }
    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/