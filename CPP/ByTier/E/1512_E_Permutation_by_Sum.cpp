// Problem: CF 1512 E - Permutation by Sum
// https://codeforces.com/contest/1512/problem/E

/*
Purpose: 
This code solves the problem of constructing a permutation of integers from 1 to n such that the sum of elements from index l to r equals a given value s. It uses a greedy approach to place the largest possible elements in the required range first, then fills the rest of the positions with remaining numbers.

Algorithm:
1. For each test case, check if the required sum s is feasible within the constraints of the range [l, r].
2. Use a greedy strategy to place the largest elements possible in the range [l, r] to achieve the sum s.
3. Fill the remaining positions with the leftover numbers in order.

Time Complexity: O(n^2) per test case due to nested loops for placing elements.
Space Complexity: O(n) for storing the permutation array and auxiliary arrays.

Techniques:
- Greedy algorithm to construct the permutation
- Pre-checking feasibility of sum before construction
- In-place filling of permutation array
*/

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
int t, n, i, l, r, s, a[501], b[501], j;
int main() {
  scanf("%d", &t);
  for (; t > 0; t--) {
    memset(b, 0, sizeof(b)); // Initialize boolean array to mark used numbers
    memset(a, 0, sizeof(a)); // Initialize result array
    scanf("%d%d%d%d", &n, &l, &r, &s); // Read inputs
    // Check if the required sum is possible within the given range
    if (s < (1 + (r - l + 1)) * (r - l + 1) / 2 ||
        s > (n + n - r + l) * (r - l + 1) / 2) {
      cout << -1 << endl;
      continue;
    }
    // Greedily assign the largest valid numbers to the required range
    for (i = n; i > 0 && s != 0; i--)
      if (s - i >= (1 + r - l) * (r - l) / 2 && s >= i) // Check if placing 'i' is valid
        s -= i, a[l++] = i, b[i] = 1; // Place 'i' in the permutation and mark it as used
    // Fill the remaining positions with unused numbers
    for (i = 1, j = 1; i <= n; i++)
      if (b[i] == 0) { // If number 'i' is not yet used
        while (a[j] != 0) // Find next empty position in result array
          j++;
        a[j++] = i; // Place unused number
      }
    // Output the resulting permutation
    for (i = 1; i <= n; i++)
      cout << a[i] << " ";
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/