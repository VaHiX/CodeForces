// Problem: CF 1051 B - Relatively Prime Pairs
// https://codeforces.com/contest/1051/problem/B

/*
 * Problem: Relatively Prime Pairs
 * 
 * Task: Given a range [l, r], split all numbers into pairs such that each pair 
 *       has a GCD of 1. The range contains an odd number of elements, so we 
 *       can form exactly (r - l + 1) / 2 pairs.
 * 
 * Approach:
 *   - Since the number of elements is odd, we can pair consecutive numbers.
 *   - For any two consecutive integers (p, p+1), their GCD is always 1.
 *   - So, we iterate from l to r in steps of 2 and pair each odd number with 
 *     the next even number.
 * 
 * Time Complexity: O((r - l + 1) / 2) = O(n), where n is the number of elements.
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll l, r;
  scanf("%lld %lld", &l, &r);
  puts("YES");
  
  // Iterate through the range and pair consecutive numbers
  for (ll p = l; p <= r; p += 2) {
    printf("%lld %lld\n", p, p + 1);
  }
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/