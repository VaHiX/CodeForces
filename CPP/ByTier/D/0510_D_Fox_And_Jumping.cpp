// Problem: CF 510 D - Fox And Jumping
// https://codeforces.com/contest/510/problem/D

/*
 * Problem: Fox And Jumping
 * Purpose: Find the minimum cost to buy cards such that Fox Ciel can jump to any cell on an infinite tape.
 *          Each card allows jumps of a specific length and has a cost.
 *          This is essentially finding the minimum cost to achieve a GCD of 1 among the selected jump lengths.
 *
 * Algorithms/Techniques:
 *   - Dynamic Programming with GCD combinations
 *   - Map-based DP to store minimum cost for each possible GCD value
 *   - For each new card, update all existing GCD values by combining with the new card's length
 *
 * Time Complexity: O(n^2 * log(max_length)) where n is the number of cards.
 *   - For each card, we iterate over all previously processed GCDs.
 *   - Computing GCD takes O(log(max_length)).
 *   - In worst case, we might have up to n different GCDs.
 *
 * Space Complexity: O(n * log(max_length)) for storing GCD values and their associated costs.
 */

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

typedef long long ll;

// Function to compute greatest common divisor
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<ll> lv(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &lv[p]);
  }
  std::vector<ll> cv(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &cv[p]);
  }
  std::map<ll, ll> f; // Map to store minimum cost for each GCD value
  for (ll p = 0; p < n; p++) {
    ll len(lv[p]), cost(cv[p]);
    // Update the cost for the current length if it's cheaper
    if ((!f.count(len)) || (cost < f[len])) {
      f[len] = cost;
    }
    // For every existing GCD, compute new GCD with current card and update cost
    for (std::map<ll, ll>::iterator it = f.begin(); it != f.end(); it++) {
      ll key = it->first;
      ll val = it->second;
      ll g = gcd(key, len); // Compute GCD of current key and new length
      // Update the cost for GCD 'g' if the new combination is cheaper
      if ((!f.count(g)) || (cost + val < f[g])) {
        f[g] = cost + val;
      }
    }
  }
  // Output result: If GCD of 1 is achievable, return its cost; otherwise return -1
  printf("%lld\n", f.count(1) ? f[1] : -1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/