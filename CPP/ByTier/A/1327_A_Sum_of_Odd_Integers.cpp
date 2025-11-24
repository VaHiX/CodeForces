// Problem: CF 1327 A - Sum of Odd Integers
// https://codeforces.com/contest/1327/problem/A

/*
 * Problem: Sum of Odd Integers
 * Task: Determine if a number n can be represented as a sum of k distinct positive odd integers.
 *
 * Algorithm/Techniques:
 * - Mathematical analysis:
 *   - The smallest possible sum of k distinct positive odd integers is 1 + 3 + 5 + ... + (2k-1) = k^2
 *   - For n to be expressible as such sum, it must satisfy:
 *     1. n >= k^2 (minimum possible sum)
 *     2. n and k have the same parity (both odd or both even)
 *       - This ensures we can construct valid odd integers with correct total sum.
 *
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    // Check if n can be written as sum of k distinct positive odd integers
    // Condition 1: n >= k^2 (minimum possible sum)
    // Condition 2: n and k have the same parity
    bool res = (n % 2 == k % 2) && (n >= k * k);
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/