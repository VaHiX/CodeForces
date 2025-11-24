// Problem: CF 1673 E - Power or XOR?
// https://codeforces.com/contest/1673/problem/E

/*
 * Problem: E. Power or XOR?
 * Purpose: Compute the XOR of all valid expressions formed by choosing either 
 *          Power or XOR operations for each '^' in the expression.
 *          An expression is valid if it uses at least k XOR operations.
 * 
 * Algorithms/Techniques:
 * - Dynamic programming with bit manipulation
 * - Preprocessing powers of 2 for fast computation
 * - Bit counting and filtering logic based on constraints
 * 
 * Time Complexity: O(n * log(max_val)) where n <= 2^20 and max_val < 2^20
 * Space Complexity: O(2^20) for the answer array and auxiliary arrays
 */
#include <iostream>

using namespace std;
long long n, k, a[1500005], fw[25];
bool ans[1500008];
int main() {
  fw[0] = 1;
  for (int i = 1; i <= 22; i++) // Precompute powers of 2 up to 2^22
    fw[i] = fw[i - 1] << 1;
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++) {
    int bas = 0;
    for (int j = i; j >= i - 20 && j >= 1; j--) { // Iterate through previous up to 20 elements
      if (bas > 20) // Early termination for large base
        break;
      if (fw[bas] * a[j] >= 1048576) // Early termination for overflow
        break;
      int s = n - 1 - (i - j) - (j != 1) - (i != n); // Number of remaining operators
      int p = k - (i != n) - (j != 1); // Number of required XOR operators after current choice
      if (p > s) // Not enough operators to satisfy condition
        continue;
      if (((s - 1) & (p - 1)) == (p - 1)) // Bit trick to check if s >= p
        ans[fw[bas] * a[j]] ^= 1; // Toggle the bit in the result array
      bas += a[j]; // Update base for next iteration
    }
  }
  int len = 1048575; // Maximum index to check for non-zero bits
  while (ans[len] == 0 && len > 0)
    len--; // Skip trailing zeros
  for (int i = len; i >= 0; i--)
    cout << ans[i]; // Print binary representation
}


// https://github.com/VaHiX/CodeForces/