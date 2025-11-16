// Problem: CF 1716 B - Permutation Chain
// https://codeforces.com/contest/1716/problem/B

/*
 * Code Purpose: Generate the longest permutation chain for a given n.
 *               A permutation chain starts with the identity permutation,
 *               and each subsequent permutation is obtained by swapping
 *               two elements in the previous one, such that the fixedness
 *               strictly decreases.
 *
 * Algorithm/Techniques:
 *   - Start with identity permutation [1, 2, ..., n]
 *   - For each step, swap elements at positions (i-1) and (i), starting from i=1
 *   - This ensures that we decrease the fixedness at each step by moving elements
 *     away from their correct positions, thus reducing the number of fixed points.
 *   - The process continues until no more swaps can decrease fixedness further.
 *
 * Time Complexity: O(n^2)
 *   - Outer loop runs n times (for each permutation in the chain)
 *   - Inner loop copies the permutation (O(n) per step)
 *   - Swapping takes O(1)
 *   - Total: O(n^2)
 *
 * Space Complexity: O(n)
 *   - We store one permutation of size n in memory at any time
 *   - Additional variables are O(1)
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      a[p] = p + 1;
    }
    printf("%ld\n", n);
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    };
    puts("");
    for (long p = 1; p < n; p++) {
      long tmp = a[p];           // Store element at position p
      a[p] = a[p - 1];           // Move element from p-1 to p
      a[p - 1] = tmp;            // Move element from p to p-1
      for (long p = 0; p < n; p++) {
        printf("%ld ", a[p]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/