// Problem: CF 1758 C - Almost All Multiples
// https://codeforces.com/contest/1758/problem/C

/*
C. Almost All Multiples
Algorithm: Greedy construction of permutation with specific divisibility constraints.
Time Complexity: O(n) amortized per test case, as each element is processed at most once across all operations.
Space Complexity: O(n) for storing the permutation vector.

The problem asks to construct a permutation of integers from 1 to n such that:
- p[1] = x
- p[n] = 1
- For all i from 1 to n-1, p[i] is a multiple of i
- The result should be lexicographically smallest among all valid permutations.

Approach:
1. Check if n % x == 0. If not, return -1.
2. Initialize vector v[1..n] such that v[i] = i for all i.
3. Set v[1] = x and v[n] = 1.
4. Iteratively assign multiples of x in increasing order to build a valid sequence:
   - Starting from x, find next multiple p such that n % p == 0
   - Assign v[x] = p, update x = p.
5. Print the resulting permutation.

This greedy strategy ensures we construct the lexicographically minimal valid permutation.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    if (n % x) {  // If n is not divisible by x, no valid permutation exists
      puts("-1");
      continue;
    }
    std::vector<long> v(n + 1);  // Vector to store the permutation (1-indexed)
    for (long p = 1; p <= n; p++) {
      v[p] = p;
    }
    v[1] = x;  // First element is x
    v[n] = 1;  // Last element is 1
    
    while (x < n) {  // While current x is less than n
      for (long p = 2 * x; p <= n; p += x) {  // Find next multiple of x that divides n
        if (n % p == 0) {
          v[x] = p;  // Assign p to the index x
          x = p;     // Update x to p for next iteration
          break;
        }
      }
    }
    
    for (long p = 1; p <= n; p++) {
      printf("%ld ", v[p]);  // Print the constructed permutation
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/