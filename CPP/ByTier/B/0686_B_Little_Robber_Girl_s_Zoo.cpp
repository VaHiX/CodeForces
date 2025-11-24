// Problem: CF 686 B - Little Robber Girl's Zoo
// https://codeforces.com/contest/686/problem/B

/*
 * Code Purpose: This program sorts an array of animal heights in non-decreasing order
 *               using a series of adjacent swaps, where each swap operation is defined
 *               by a range [l, r] such that r - l + 1 is even.
 *               The algorithm uses a bubble-sort-like approach, repeatedly scanning
 *               the array and swapping adjacent elements if they are in wrong order.
 *
 * Algorithms/Techniques: Bubble Sort with specific swap segments
 *
 * Time Complexity: O(n^3) in worst case due to nested loops and potential multiple swaps.
 *                  However, in practice it's much faster because each operation
 *                  reduces the number of inversions.
 *
 * Space Complexity: O(n) for storing the array of animal heights.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld\n", &n);  // Read number of animals
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);  // Read heights of animals
  }
  // Bubble sort-like approach to sort the array
  for (long p = 0; p < n; p++) {
    for (long q = n - 1; q > p; q--) {
      if (a[q - 1] > a[q]) {  // If adjacent elements are in wrong order
        printf("%ld %ld\n", q, q + 1);  // Output segment [q, q+1] for swapping
        long temp = a[q - 1];  // Swap elements
        a[q - 1] = a[q];
        a[q] = temp;
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/