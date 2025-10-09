// Problem: CF 2086 B - Large Array and Segments
// https://codeforces.com/contest/2086/problem/B

/*
B. Large Array and Segments

Purpose:
This code solves the problem of counting the number of starting positions l in a repeated array b (formed by repeating array a k times) such that there exists a position r >= l where the sum of elements from l to r is at least x.

Approach:
1. For each test case, compute the total sum of original array 'a' as 's'.
2. Compute how many full cycles of 'a' are used in constructing 'b', and adjust the remaining portion of 'x' using modular arithmetic.
3. Count the number of "valid" starting positions in the last partial cycle:
   - Use sliding window logic to count valid segments where prefix sums exceed x.
4. Adjust final count based on how many full cycles contribute to valid ranges.

Time Complexity: O(n) per test case, since we iterate through array a once for each test.
Space Complexity: O(n), due to storing the input array a.

Algorithms/Techniques:
- Modular arithmetic
- Prefix sum concepts
- Sliding window idea
- Greedy approach with backward iteration
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k, x;
    scanf("%lld %lld %lld", &n, &k, &x);
    std::vector<ll> a(n);
    ll s(0); // total sum of array a
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      s += a[p]; // accumulate sum
    }
    ll cnt(n * k); // initially all positions are counted
    cnt -= (x / s) * n; // subtract full cycles contributing to the total
    x %= s; // remaining x after full cycles
    cnt += (!x); // if x is exactly divisible by s, adjust accordingly
    for (ll p = n - 1; x > 0 && cnt > 0 && p >= 0; p--) {
      x -= a[p]; // decrease x by current element
      if (x <= 0) {
        break; // we've found sufficient elements to cover x
      }
      --cnt; // decrement counter as no valid range can be formed from this position onward
    }
    cnt = (cnt > 0 ? cnt : 0); // ensure non-negative result
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/