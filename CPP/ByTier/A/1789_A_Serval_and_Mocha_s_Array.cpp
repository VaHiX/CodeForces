// Problem: CF 1789 A - Serval and Mocha's Array
// https://codeforces.com/contest/1789/problem/A

/*
 * Problem: A. Serval and Mocha's Array
 * Purpose: Determine if an array can be reordered to make it "beautiful".
 *          An array is beautiful if all its prefixes of length >= 2 are "good".
 *          An array is good if gcd of all elements <= array length.
 *
 * Algorithm:
 * - For each test case, we check if there exists any pair of elements whose GCD is at most 2.
 * - If such a pair exists, we can potentially reorder the array to make it beautiful.
 * - Time Complexity: O(n^2 * log(max(a))) where n <= 100 and log(max(a)) is for GCD computation.
 * - Space Complexity: O(n) for storing the array elements.
 */

#include <cstdio>
#include <vector>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read array elements
    }
    bool res(false);
    for (long p = 0; !res && p < n; p++) {
      for (long q = p + 1; !res && q < n; q++) {
        if (gcd(a[p], a[q]) <= 2) { // Check if any pair has GCD <= 2
          res = true;
        }
      }
    }
    puts(res ? "Yes" : "No"); // Output result based on whether such pair exists
  }
}


// https://github.com/VaHiX/codeForces/