// Problem: CF 788 A - Functions again
// https://codeforces.com/contest/788/problem/A

/*
 * Problem: Maximum value of a specific function f defined over all subarrays.
 * Algorithm: Kadane's algorithm adapted for this problem. The key insight is to track
 *            the maximum difference between adjacent elements while maintaining a
 *            running maximum of the function value.
 * 
 * Time Complexity: O(n) - single pass through the array
 * Space Complexity: O(1) - only using a few variables for computation
 */

#include <bits/std_abs.h>
#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;
long long n, a1, a2, b, c, d, t, f;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> a1;  // Read the first element of the array
  while (--n) {    // Loop through remaining elements
    cin >> a2;     // Read next element
    b = abs(a1 - a2);  // Compute absolute difference between adjacent elements
    a1 = a2;       // Move to next element
    t = c;         // Store previous value of c
    c = max(b, d + b);  // Update c using Kadane's logic for max subarray
    f = max(f, c); // Keep track of global maximum
    d = t - b;     // Update d for next iteration
  }
  cout << f;  // Output the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/