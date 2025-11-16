// Problem: CF 2071 B - Perfecto
// https://codeforces.com/contest/2071/problem/B

/*
 * Problem: Perfecto
 * Algorithm: Constructive approach with perfect square check
 *
 * Time Complexity: O(n log n) per test case due to set operations and loop over
 * n elements. Space Complexity: O(n) for storing the set of perfect squares and
 * the permutation vector.
 *
 * Approach:
 * 1. Precompute all perfect squares up to 5*10^5 (since n <= 5*10^5).
 * 2. For each test case:
 *    - If the total sum of integers from 1 to n is a perfect square, return -1.
 *    - Else, construct a permutation such that no prefix sum is a perfect
 * square.
 *    - Use a greedy strategy: when placing an element, if adding it makes the
 * prefix sum a perfect square, swap the current element with the next one in
 * sequence and add that to the current position.
 */

#include <cstdio>
#include <set>
#include <vector>
typedef long long ll;

int main() {
  // Precompute all perfect squares up to 5*10^5
  std::set<ll> ssq;
  for (ll p = 1; p <= 5e5; p++) {
    ssq.insert(p * p);
  }

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);

    // If total sum is a perfect square, impossible to construct a valid
    // permutation
    if (ssq.count(n * (n + 1) / 2)) {
      puts("-1");
      continue;
    }

    std::vector<ll> v(n, -1);
    ll cs(0); // cumulative sum

    for (ll p = 0; p < n; p++) {
      if (v[p] < 0) {
        ll cur = p + 1;

        // If adding 'cur' to current prefix sum results in a perfect square,
        // we need to avoid this by swapping the next number into place
        if (ssq.count(cs + cur)) {
          v[p] = cur + 1; // Place the next number first
          v[p + 1] = cur; // Swap with current number
        } else {
          v[p] = cur; // Otherwise place it normally
        }
      }
      cs += v[p]; // update cumulative sum
    }

    for (ll p = 0; p < n; p++) {
      printf("%lld ", v[p]);
    }
    puts("");
  }
}

// https://github.com/VaHiX/CodeForces/