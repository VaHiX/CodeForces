// Problem: CF 1151 D - Stas and the Queue at the Buffet
// https://codeforces.com/contest/1151/problem/D

/*
 * Problem: D. Stas and the Queue at the Buffet
 *
 * Purpose: Minimize the total dissatisfaction of students in a queue by rearranging their order.
 *          Each student i has characteristics a_i and b_i. The dissatisfaction of a student at position j is:
 *          a_i * (j - 1) + b_i * (n - j)
 *
 * Algorithm:
 *   - For each student i, calculate the "value" as (b_i - a_i)
 *   - Sort students by this value in ascending order
 *   - Compute the total dissatisfaction using the sorted order
 *
 * Time Complexity: O(n log n) due to sorting
 * Space Complexity: O(n) for storing the vector of pairs
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  // Vector stores (b_i - a_i, {a_i, b_i}) for each student
  std::vector<std::pair<ll, std::pair<ll, ll>>> v(n);
  for (ll p = 0; p < n; p++) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    // Precompute the key value (b - a) used for sorting
    v[p].first = b - a;
    v[p].second = std::make_pair(a, b);
  }
  // Sort by (b_i - a_i) to determine optimal order
  sort(v.begin(), v.end());
  ll res(0);
  // Compute total dissatisfaction based on the sorted order
  for (ll p = 0; p < n; p++) {
    // Position p contributes: p * a_i + (n - 1 - p) * b_i
    res += p * (v[p].second.first) + (n - 1 - p) * v[p].second.second;
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/