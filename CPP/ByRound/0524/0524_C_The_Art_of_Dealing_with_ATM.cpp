// Problem: CF 524 C - The Art of Dealing with ATM
// https://codeforces.com/contest/524/problem/C

/*
 * Problem: The Art of Dealing with ATM
 * 
 * Algorithm/Technique:
 * - Brute-force approach with optimization
 * - For each withdrawal amount, we try to express it as a sum of at most k bills
 *   with at most 2 distinct denominations.
 * - We iterate over all denominations and for each denomination, we try using
 *   up to k bills of that denomination and then check if the remainder can be
 *   formed using at most (k - used_bills) bills of one other denomination.
 * 
 * Time Complexity: O(n * k^2 * log(n) + q * n * k^2)
 *   - n * k^2 for checking combinations of bills for each query
 *   - log(n) for set operations
 *   - q queries
 * 
 * Space Complexity: O(n)
 *   - Space for storing the denominations in a set
 */

#include <cstdio>
#include <set>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::set<long> ds;
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ds.insert(x);  // Insert all denominations into a set for fast lookup
  }
  long q;
  scanf("%ld", &q);
  while (q--) {
    long x;
    scanf("%ld", &x);
    long mb(k + 1);  // mb stores minimum bills needed, initialized to k+1 (impossible)
    for (std::set<long>::iterator it = ds.begin(); it != ds.end(); it++) {
      long den = *it;
      // If x is divisible by denomination and number of bills needed is within limit
      if (x % den == 0 && x / den <= k) {
        mb = (mb < (x / den)) ? mb : (x / den);
      }
      // Try using p bills of current denomination
      for (long p = 1; p <= k; p++) {
        long rem = x - p * den;
        if (rem <= 0) {
          break;  // No more need to check larger p
        }
        // Try using q bills of another denomination
        for (long q = 1; q + p <= k && q + p < mb; q++) {
          if (rem % q != 0) {
            continue;  // Skip if remainder cannot be split evenly
          }
          if (ds.count(rem / q)) {  // Check if the quotient is a valid denomination
            mb = q + p;  // Update minimum bills count
          }
        }
      }
    }
    printf("%ld\n", (mb <= k) ? mb : -1);  // Print result or -1 if impossible
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/