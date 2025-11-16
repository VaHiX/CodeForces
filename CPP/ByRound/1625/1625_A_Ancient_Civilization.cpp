// Problem: CF 1625 A - Ancient Civilization
// https://codeforces.com/contest/1625/problem/A

/*
 * Problem: Ancient Civilization
 * Algorithm: For each bit position, count how many times 1 appears across all numbers.
 *            If more than half of the numbers have a 1 in that position,
 *            set the result bit to 1; otherwise, set it to 0.
 *
 * Time Complexity: O(n * l) where n is number of forms and l is length of words
 * Space Complexity: O(l) for vector storing bit counts
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, len;
    scanf("%ld %ld", &n, &len);
    std::vector<long> v(len, 0); // Count of 1s at each bit position
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      for (long u = 0; u < len; u++) {
        v[u] += x % 2; // Add the least significant bit to the count
        x /= 2;        // Shift right to check next bit
      }
    }
    long res(0);
    for (long p = len - 1; p >= 0; p--) {
      // If more than half are 1s, choose 1; otherwise 0
      res = 2 * res + ((2 * v[p] <= n) ? 0 : 1);
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/