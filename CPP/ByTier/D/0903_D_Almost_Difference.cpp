// Problem: CF 903 D - Almost Difference
// https://codeforces.com/contest/903/problem/D

/*
 * Code Purpose: Calculate the sum of a function d(ai, aj) over all pairs (i, j) where i <= j.
 * The function d(x, y) is defined as:
 *   - 0 if x == y
 *   - 1 if x == y + 1
 *   - -1 if x == y - 1
 *   - 0 otherwise
 *
 * Algorithm:
 * - Use a map to store frequency of elements seen so far.
 * - For each element, compute contribution to the total based on previous elements.
 * - Adjust total using the map's stored counts for x-1 and x+1.
 * - Time Complexity: O(n log n) due to map operations.
 * - Space Complexity: O(n) for the map storing element frequencies.
 */

#include <cstdio>
#include <map>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  std::map<ll, ll> m; // Map to store frequency of elements
  long double total(0); // Total sum of d(ai, aj) values
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    // Accumulate contribution of current element based on previous elements
    total += x * (2 * p - n + 1);
    // Subtract contributions from elements that are x-1
    if (m.count(x - 1)) {
      total -= m[x - 1];
    }
    // Add contributions from elements that are x+1
    if (m.count(x + 1)) {
      total += m[x + 1];
    }
    // Increment frequency of current element
    ++m[x];
  }
  printf("%.0Lf\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/