// Problem: CF 1693 A - Directional Increase
// https://codeforces.com/contest/1693/problem/A

/*
 * Problem: Determine if a given array can be achieved using specific operations on a pointer.
 *          The pointer starts at index 0 and must return to index 0 at the end.
 *          Two operations allowed:
 *          1. Move right: increase current element by 1 and move pointer right (if not at end)
 *          2. Move left: decrease current element by 1 and move pointer left (if not at start)
 *
 * Algorithm:
 *   - Compute prefix sums of the array to simulate the operations.
 *   - Check that all prefix sums are non-negative (since we can only go up and down with a valid sequence).
 *   - Verify total sum is zero (pointer must return to start).
 *   - Ensure that after encountering zero, no non-zero values appear later (to maintain constraint on pointer position).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
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
    std::vector<ll> a(n);
    bool ans(true);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      if (p > 0) {
        a[p] += a[p - 1]; // prefix sum calculation
      }
      if (a[p] < 0) {
        ans = false; // if prefix sum is negative, impossible to reach this point without going below zero
      }
    }
    if (a.back() != 0) {
      ans = false; // total sum must be zero for pointer to return to start
    }
    bool zero(false);
    for (ll p = 0; ans && p < n; p++) {
      if (a[p] && zero) {
        ans = false; // after seeing a zero, all subsequent values must also be zero
      } else if (!a[p]) {
        zero = true;
      }
    }
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/