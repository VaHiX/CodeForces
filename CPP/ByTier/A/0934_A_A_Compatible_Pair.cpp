// Problem: CF 934 A - A Compatible Pair
// https://codeforces.com/contest/934/problem/A

/*
 * Code Purpose: 
 *   Find the brightness of the pair of lanterns formed when Tommy hides one of his lanterns,
 *   and Banban chooses one of the remaining lanterns from Tommy and one from his own.
 *   Tommy wants to minimize the resulting product, while Banban wants to maximize it.
 *   The algorithm computes the maximum possible product for each possible hidden lantern
 *   and then selects the second-highest among those maximums.
 * 
 * Algorithms/Techniques:
 *   - Brute-force for each hidden lantern from Tommy's set
 *   - For each hidden lantern, compute the maximum product Banban can form
 *   - Sort results and pick the second largest value
 * 
 * Time Complexity: O(n * m + n * log(n)) where n and m are the sizes of arrays a and b.
 *   - O(n * m) to compute all max products for each hidden lantern
 *   - O(n * log(n)) for sorting the max products
 * 
 * Space Complexity: O(n) for storing temporary max products
 */
#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> a(n), b(m), c(n, -2e18); // c stores maximum product for each hidden lantern
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &a[p]);
  }
  for (ll p = 0; p < m; p++) {
    scanf("%lld", &b[p]);
  }
  // For each lantern Tommy hides, calculate the maximum product Banban can produce
  for (ll p = 0; p < n; p++) {
    for (ll q = 0; q < m; q++) {
      c[p] = (c[p] > a[p] * b[q]) ? c[p] : (a[p] * b[q]); // Keep track of max product for this hidden lantern
    }
  }
  sort(c.begin(), c.end()); // Sort the maximum products
  printf("%lld\n", c[c.size() - 2]); // Output the second largest (i.e., optimal choice for Tommy)
  return 0;
}


// https://github.com/VaHiX/CodeForces/