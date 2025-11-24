// Problem: CF 1844 B - Permutations & Primes
// https://codeforces.com/contest/1844/problem/B

/*
 * Problem: B. Permutations & Primes
 * 
 * Algorithm/Technique: Greedy construction of permutation to maximize MEX prime pairs.
 * 
 * Time Complexity: O(n) per test case, as we only iterate through the array once to assign values.
 * Space Complexity: O(n) for storing the permutation array.
 * 
 * The idea is to construct a permutation such that as many subarrays as possible have a MEX that is a prime number.
 * By placing small values strategically (like 1, 2, 3) and filling in remaining positions with larger numbers,
 * we can increase the count of valid (prime MEX) subarrays.
 * 
 * The solution works as follows:
 * - For n = 1, return [1].
 * - For n = 2, return [2, 1].
 * - For n > 2:
 *   - Place 2 at the start (a[0]).
 *   - Place 1 at the middle (a[n/2]).
 *   - Place 3 at the end (a[n-1]).
 *   - Fill the rest of the positions from left to right with consecutive integers starting from 4.
 * This construction helps in maximizing the number of prime MEX values across all subarrays.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("1");
      continue;
    } else if (n == 2) {
      puts("2 1");
      continue;
    }
    std::vector<long> a(n, 0);
    a[0] = 2;                    // Place 2 at the beginning
    a[n / 2] = 1;                // Place 1 in the middle
    a[n - 1] = 3;                // Place 3 at the end
    long cur(4);                 // Start filling from 4
    for (long p = 1; p + 1 < n; p++) {
      if (a[p]) {
        continue;               // Skip already filled positions
      }
      a[p] = cur;               // Fill remaining positions with increasing numbers
      cur++;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);     // Print the constructed permutation
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/