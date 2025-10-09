// Problem: CF 2128 A - Recycling Center
// https://codeforces.com/contest/2128/problem/A

/*
 * Problem: A. Recycling Center
 * Purpose: Determine the minimum number of coins to destroy all trash bags,
 *          where each bag's weight doubles after each destruction step.
 * Algorithms/Techniques: Greedy algorithm with sorting.
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the weights.
 */
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, c;
    scanf("%lld %lld", &n, &c);
    std::vector<ll> w(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &w[p]); // Read the weight of each trash bag
    }
    sort(w.rbegin(), w.rend()); // Sort weights in descending order to process heavier bags first
    ll mult(1), cnt(0);        // 'mult' tracks the current multiplier, 'cnt' counts coins spent
    for (ll p = 0; p < n; p++) {
      if (mult * w[p] > c) {   // If current weight exceeds limit 'c'
        ++cnt;                 // Spend one coin
      } else {
        mult *= 2;             // Otherwise, double the multiplier for next steps
      }
    }
    printf("%lld\n", cnt);     // Output total coins spent
  }
}


// https://github.com/VaHiX/codeForces/