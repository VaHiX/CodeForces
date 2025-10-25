// Problem: CF 1250 J - The Parade
// https://codeforces.com/contest/1250/problem/J

/*
 * Problem: J. The Parade
 * Purpose: Find the maximum number of soldiers that can participate in a parade
 *          such that they are arranged into k rows with equal count and no two
 *          soldiers in a row have heights differing by more than 1.
 *
 * Algorithm: Binary search on the answer (maximum height difference allowed per row),
 *            combined with a greedy validation function to check if a given number
 *            of soldiers can be arranged into k rows under constraints.
 *
 * Time Complexity: O(n * log(S)) where S is the sum of all soldiers across all heights,
 *                  and n is the maximum number of distinct heights in a test case.
 * Space Complexity: O(n) for storing the count of soldiers by height.
 */

#include <cstdio>
#include <vector>
typedef long long ll;

// Function to check if we can form 'rows' number of rows with each row having at least 't' soldiers.
bool check(const std::vector<ll> &h, ll rows, ll t) {
  if (t <= 0) {
    return true;
  }
  ll cnt(0), avail(0);
  for (ll p = 0; p < h.size() && cnt < rows; p++) {
    ll total = avail + h[p];       // Total soldiers available to form rows at this height
    cnt += (total / t);            // Count how many complete rows can be formed
    avail = total % t;             // Remaining soldiers that couldn't form a full row
    avail = (h[p] < avail) ? h[p] : avail;  // Update available soldiers for next iteration
  }
  return (cnt >= rows);            // Return true if we could form enough rows
}

int main() {
  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll sumc(0);
    std::vector<ll> c(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &c[p]);
      sumc += c[p];
    }
    ll left(0), right(1 + sumc / k), res(0);
    while (left <= right) {
      ll mid = (left + right) / 2;      // Midpoint of binary search range
      if (check(c, k, mid)) {           // If arrangement is possible with 'mid' soldiers per row
        res = mid * k;                  // Update result with total number of soldiers
        left = mid + 1;                 // Try to increase the number of soldiers per row
      } else {
        right = mid - 1;                // Reduce number of soldiers per row
      }
    }
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/