// Problem: CF 1475 C - Ball in Berland
// https://codeforces.com/contest/1475/problem/C

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, k;
    scanf("%lld %lld %lld", &a, &b, &k);
    std::vector<ll> boy(k); // boy[i] stores the boy index of the i-th pair
    std::vector<ll> db(a, 0); // db[i] counts how many times boy i appears in pairs
    for (ll p = 0; p < k; p++) {
      scanf("%lld", &boy[p]);
      --boy[p]; // Convert to 0-based indexing
      ++db[boy[p]]; // Increment count of this boy
    }
    std::vector<ll> girl(k); // girl[i] stores the girl index of the i-th pair
    std::vector<ll> dg(b, 0); // dg[i] counts how many times girl i appears in pairs
    for (ll p = 0; p < k; p++) {
      scanf("%lld", &girl[p]);
      --girl[p]; // Convert to 0-based indexing
      ++dg[girl[p]]; // Increment count of this girl
    }
    ll res(0); // Result counter for valid pairs of pairs
    for (ll p = 0; p < k; p++) {
      // For each pair (boy[p], girl[p]), the number of valid second pairs is:
      // total pairs - pairs involving same boy - pairs involving same girl + 1 (to avoid double subtraction)
      res += k - db[boy[p]] - dg[girl[p]] + 1;
    }
    printf("%lld\n", res / 2); // Divide by 2 since each pair is counted twice
  }
}
/*
 * Problem: C. Ball in Berland
 *
 * Purpose:
 *   Given a set of possible boy-girl pairs, select two pairs such that no person appears in more than one pair.
 *   Count all valid combinations of two such pairs.
 *
 * Algorithms/Techniques:
 *   - Preprocessing step to count how many times each boy and girl appear in pairs
 *   - For each pair (b_i, g_i), compute the number of valid second pairs using inclusion-exclusion principle
 *   - Avoid double counting by dividing result by 2 at the end
 *
 * Time Complexity: O(k + a + b)
 *   - Each loop processes k elements, and array initialization takes O(a) and O(b) time.
 *
 * Space Complexity: O(k + a + b)
 *   - Storing vectors for boy and girl indices, and counting arrays for db and dg.
 */

// https://github.com/VaHiX/codeForces/