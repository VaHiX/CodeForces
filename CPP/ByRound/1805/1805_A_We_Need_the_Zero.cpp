// Problem: CF 1805 A - We Need the Zero
// https://codeforces.com/contest/1805/problem/A

/*
 * Purpose: Determine if there exists a value x such that XOR of all elements 
 *          in the transformed array b[i] = a[i] XOR x equals 0.
 *          
 * Algorithm: 
 *   - Compute XOR of all elements in the original array (call it 'cs').
 *   - If n is odd, x = cs satisfies the condition.
 *   - If n is even, then for the XOR of transformed array to be 0, 
 *     it's necessary that cs = 0. If so, x = 0 works; otherwise, no valid x exists.
 *   
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a few variables.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cs(0);  // Initialize cumulative XOR
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cs = cs ^ x;  // XOR each element with cs
    }
    if (n % 2) {
      // If n is odd, choosing x = cs ensures b1 ^ b2 ^ ... ^ bn = 0
      printf("%ld\n", cs);
    } else {
      // If n is even, then for XOR to be 0, cs must be 0
      printf("%d\n", cs ? -1 : 0);
    }
  }
}


// https://github.com/VaHiX/CodeForces/