// Problem: CF 2040 A - Game of Division
// https://codeforces.com/contest/2040/problem/A

/*
 * Problem: Game of Division
 * Algorithm: Using modular arithmetic to detect if there exists a pair of elements
 *            such that their difference is not divisible by k.
 * 
 * Time Complexity: O(n * k) per test case, where n is the size of array and k is given.
 * Space Complexity: O(k) for the vector v to store indices of remainders.
 *
 * Techniques:
 * - Modular arithmetic
 * - Hashing using remainder buckets
 * - Greedy approach to find first valid index
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n, 0), v(k, 0); // v[i] stores first index of remainder i, or -1 if multiple indices
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      long m = a[p] % k; // Compute remainder when dividing by k
      if (v[m] < 0) {
        continue; // Skip if already marked as having multiple occurrences
      } else if (!v[m]) {
        v[m] = p + 1; // Store first occurrence index (1-based)
      } else {
        v[m] = -1; // Mark as occurring more than once
      }
    }
    long res(-1);
    for (long p = 0; res < 0 && p < k; p++) {
      if (v[p] > 0) {
        res = v[p]; // Found first index with unique remainder
        break;
      }
    }
    if (res > 0) {
      printf("YES\n%ld\n", res);
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/