// Problem: CF 870 C - Maximum splitting
// https://codeforces.com/contest/870/problem/C

/*
 * Problem: Maximum splitting into composite numbers
 * 
 * Algorithm:
 * - All integers greater than 11 can be represented as a sum of composite numbers.
 * - The optimal strategy is to use as many 4s as possible, since 4 is the smallest composite number.
 * - For odd numbers, we subtract one 4 to make the remaining number even, then split it into 4s.
 * - Special cases are numbers less than 4, and 5, 7, 11 which are primes and cannot be split into composites.
 * 
 * Time Complexity: O(q), where q is the number of queries
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    long div = n / 4;  // Initial count of 4s we can use
    if (n <= 3 || n == 5 || n == 7 || n == 11) {
      // These numbers cannot be split into composite summands
      puts("-1");
      continue;
    }
    if (n & 1) {
      // If n is odd, we need to adjust the count
      // Subtract 1 from div to account for one 3 or 5 being used
      --div;
    }
    printf("%ld\n", div);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/