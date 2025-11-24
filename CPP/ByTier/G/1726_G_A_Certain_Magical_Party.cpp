// Problem: CF 1726 G - A Certain Magical Party
// https://codeforces.com/contest/1726/problem/G

/*
 * Problem: G. A Certain Magical Party
 * 
 * Purpose: This code counts the number of valid speaking orders where all people end up with equal happiness.
 * 
 * Algorithm:
 * - We use combinatorics and carefully count valid permutations based on the happiness values and personalities.
 * - The key idea is to arrange people in such a way that when they tell stories, the happiness updates are consistent with the final equality requirement.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Prefix sums (implicit via variable `have`)
 * - Modular arithmetic
 * - Sorting and linear scan
 * - Factorial precomputation
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 6e5 + 5, mod = 998244353;
int n, ans, have, a[N], fac[N], c[N][2]; // c[i][0] = count of people with happiness i and personality 0, c[i][1] = same for personality 1
int main() {
  scanf("%d", &n), ans = fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    fac[i] = (ll)fac[i - 1] * i % mod; // Precompute factorials modulo 998244353
  }
  int mn = *min_element(a + 1, a + 1 + n);
  int mx = *max_element(a + 1, a + 1 + n);
  int T = mn + n - 1; // Target value based on min happiness and number of people
  if (T < mx)
    return puts("0"), 0;  // Impossible if max happiness exceeds T
  if (mx == mn)
    return printf("%d\n", fac[n]), 0; // All same, so total permutations
  for (int i = 1, b; i <= n; ++i)
    scanf("%d", &b), ++c[a[i]][b]; // Count people by happiness and personality
  for (int i = 1; i <= c[T][1]; ++i)
    ans = (ll)ans * (n - i + 1) % mod; // Multiply by permutations of people with personality 1 at target happiness
  for (int i = mn; i <= mx; ++i) {
    if (c[i][0] && have < T - i)
      return puts("0"), 0; // If people with personality 0 exist but not enough preceding items, impossible
    have += c[i][0], ans = (ll)ans * fac[c[i][0]] % mod; // Add to have, and multiply by factorial of those with personality 0
    if (i < T && c[i][1] && (c[i][1] > 1 || have < i - mn))
      return puts("0"), 0; // If we have at least 2 with personality 1 or not enough items before them, impossible
    have += c[i][1]; // Add to have for next iteration
  }
  return printf("%d\n", ans), 0; // Output result
}


// https://github.com/VaHiX/CodeForces/