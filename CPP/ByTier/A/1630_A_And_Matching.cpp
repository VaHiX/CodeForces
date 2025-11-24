// Problem: CF 1630 A - And Matching
// https://codeforces.com/contest/1630/problem/A

/*
 * Problem: A. And Matching
 * Purpose: Given a set of n elements {0, 1, ..., n-1}, find n/2 pairs such that 
 *          the sum of bitwise ANDs of each pair equals k.
 * Algorithm: 
 *   - Special cases handling for k = 0, k = n-1, and k >= n-1.
 *   - For k < n-1, uses a specific pairing strategy based on XOR properties.
 * Time Complexity: O(n) per test case due to looping up to n/2.
 * Space Complexity: O(n) for storing pairs in vectors a and b.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n / 2), b(n / 2); // Vectors to store pairs
    if (!k) {
      // When k is 0, we make pairs so that each element ANDs with its complement (n-1)
      for (long p = 0; p < n / 2; p++) {
        a[p] = p;
        b[p] = p ^ (n - 1);
      }
    } else if (k < n - 1) {
      // For k < n-1, build a special pairing considering XOR relationship between k and (n-1)
      long q = (k ^ (n - 1));  // Complement of k in terms of (n-1)
      long m = (k < q ? k : q); // Minimum of k and q
      for (long p = 0; p < n / 2; p++) {
        if (!p) {
          // First pair uses special logic to start the construction
          a[p] = 0;
          b[p] = q;
        } else if (p == m) {
          // At position m, place k and n-1 to contribute k to the sum
          a[p] = k;
          b[p] = n - 1;
        } else {
          // Default case: pair element p with its XOR complement
          a[p] = p;
          b[p] = (p ^ (n - 1));
        }
      }
    } else if (k == n - 1) {
      // When k = n-1, special construction needed. If n == 4, impossible.
      if (n == 4) {
        puts("-1");
        continue;
      }
      // Set up a specific triplet construction
      a[0] = n - 2;
      b[0] = n - 1;
      a[1] = 1;
      b[1] = n - 3;
      a[2] = 0;
      b[2] = 2;
      for (long p = 3; p < n / 2; p++) {
        // Remainder of pairs follow default pattern
        a[p] = p;
        b[p] = p ^ (n - 1);
      }
    }
    // Print the constructed pairs
    for (long p = 0; p < n / 2; p++) {
      printf("%ld %ld\n", a[p], b[p]);
    }
  }
}


// https://github.com/VaHiX/codeForces/