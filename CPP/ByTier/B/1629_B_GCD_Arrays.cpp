// Problem: CF 1629 B - GCD Arrays
// https://codeforces.com/contest/1629/problem/B

/*
B. GCD Arrays
Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithm:
- For a range [l, r], we need to determine if it's possible to make the GCD of the array greater than 1
  with at most k operations.
- Each operation removes two elements and inserts their product.
- The key insight is that for the final GCD to be > 1, all remaining numbers must share a common factor > 1.
- If l == r, then we just check if that number is greater than 1.
- Otherwise, we calculate how many odd numbers exist in the range [l, r]:
    - Count of odds = (r - l + 1) / 2 + ((l % 2) && (r % 2))
    - If k >= count of odds, it is possible to reduce the array such that GCD > 1.
      For example, if we have enough operations, we can pair up even numbers and odd numbers to create products,
      which might allow us to generate elements with common factors.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, k;
    scanf("%ld %ld %ld", &l, &r, &k);
    if (l == r) {
      puts(r > 1 ? "YES" : "NO"); // If the only number is > 1, gcd can be > 1
      continue;
    }
    // Count of odd numbers in range [l, r]
    long odds = (r - l + 1) / 2 + ((l % 2) && (r % 2));
    puts(k >= odds ? "YES" : "NO"); // If we have enough operations to eliminate all odds, answer is YES
  }
}


// https://github.com/VaHiX/codeForces/