// Problem: CF 740 A - Alyona and copybooks
// https://codeforces.com/contest/740/problem/A

/*
 * Problem: Alyona and copybooks
 * Purpose: Find the minimum cost to buy additional copybooks such that total copybooks is divisible by 4.
 * 
 * Algorithm:
 * - Since we want n + k to be divisible by 4, we compute n % 4 to determine how many more copybooks are needed.
 * - For each case of remainder (1, 2, 3), we evaluate the minimal cost using combinations of packs:
 *   - 1 copybook: cost 'a'
 *   - 2 copybooks: cost 'b' 
 *   - 3 copybooks: cost 'c'
 * - We consider all valid combinations to minimize the total cost.
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few variables used
 */

#include <cstdio>
int main() {
  long long n, a, b, c;
  scanf("%lld %lld %lld %lld", &n, &a, &b, &c);
  n %= 4;
  long long ans(0);
  if (n == 1) {
    // To make n + k divisible by 4, we need to add 3 copybooks.
    // We can do this either by buying 3 single packs (3*a) or one pack of 3 (c).
    // Or we can buy 1 pack of 2 + 1 pack of 1 (b + a).
    ans = (c < 3 * a) ? c : (3 * a);
    ans = (ans < (a + b)) ? ans : (a + b);
  } else if (n == 2) {
    // To make n + k divisible by 4, we need to add 2 copybooks.
    // We can do this either by buying 2 single packs (2*a) or one pack of 2 (b).
    // Or we can buy 2 packs of 3 (2*c), which is inefficient, so we ignore it.
    ans = (b < 2 * a) ? b : (2 * a);
    ans = (ans < 2 * c) ? ans : (2 * c);
  } else if (n == 3) {
    // To make n + k divisible by 4, we need to add 1 copybook.
    // We can do this by buying 1 pack of 1 (a) or three packs of 1 (3*c) or 1 pack of 2 + 1 pack of 1 (b + c).
    ans = (a < 3 * c) ? a : (3 * c);
    ans = (ans < b + c) ? ans : (b + c);
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/