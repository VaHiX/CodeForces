// Problem: CF 1838 B - Minimize Permutation Subarrays
// https://codeforces.com/contest/1838/problem/B

/*
 * Problem: B. Minimize Permutation Subarrays
 * 
 * Purpose: Given a permutation of size n, we need to minimize the number of 
 *          subarrays that are permutations by swapping exactly two elements.
 * 
 * Algorithm:
 *   - Identify positions of elements 1, 2, and n in the permutation.
 *   - Consider all possible orderings of these three elements in the array.
 *   - For each valid configuration, determine the best pair of indices to swap,
 *     which minimizes the number of permutation subarrays.
 *   - The optimal strategy is to swap one of the elements in such a way that
 *     it disrupts the longest increasing subsequence or reduces the count of 
 *     valid permutations as much as possible.
 * 
 * Time Complexity: O(n) per test case — we loop through the array once to find positions.
 * Space Complexity: O(1) — only a constant amount of additional space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long one(0), two(0), fin(0); // Positions of elements 1, 2, and n
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == 1) {
        one = p;  // Store index of element 1
      } else if (x == 2) {
        two = p;  // Store index of element 2
      } else if (x == n) {
        fin = p;  // Store index of element n
      }
    }
    long left(1), right(1);  // Default indices to swap
    
    // Determine the swap positions based on relative order of 1, 2, and n
    if (one < two && two < fin) {
      // Order: 1 < 2 < n
      left += two;   // Swap 2 with its left neighbor
      right += fin;
    } else if (two < one && one < fin) {
      // Order: 2 < 1 < n
      left += one;
      right += fin;
    } else if (fin < one && one < two) {
      // Order: n < 1 < 2
      left += fin;
      right += one;
    } else if (fin < two && two < one) {
      // Order: n < 2 < 1
      left += fin;
      right += two;
    }
    
    printf("%ld %ld\n", left, right);
  }
}


// https://github.com/VaHiX/CodeForces/