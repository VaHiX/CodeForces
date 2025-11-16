// Problem: CF 798 C - Mike and gcd problem
// https://codeforces.com/contest/798/problem/C

/*
 * Problem: Mike and gcd problem
 * Algorithm/Techniques: GCD calculation, parity analysis, greedy approach
 *
 * Time Complexity: O(n * log(max(a[i])))
 * Space Complexity: O(n)
 *
 * The solution works by:
 * 1. Calculating the GCD of all elements in the array.
 * 2. If the GCD is already greater than 1, no operations are needed.
 * 3. Otherwise, we analyze the parity (odd/even) of elements to determine
 *    the minimum number of operations required to make the GCD > 1.
 *    This is done by counting odd numbers and using a greedy strategy
 *    to minimize the operations.
 */

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 1, 0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long g(0), odds(0), count(0);
  for (long p = 0; p <= n; p++) {
    g = gcd(a[p], g);  // Update GCD of all elements seen so far
    if (a[p] % 2) {    // If current element is odd
      ++odds;
    } else {           // If current element is even
      count += (odds / 2) + 2 * (odds % 2);  // Add operations needed for the group of odds
      odds = 0;          // Reset odd count
    }
  }
  puts("YES");
  printf("%ld\n", (g > 1) ? 0 : count);  // If GCD > 1, 0 operations. Else, output computed count
  return 0;
}


// https://github.com/VaHiX/CodeForces/