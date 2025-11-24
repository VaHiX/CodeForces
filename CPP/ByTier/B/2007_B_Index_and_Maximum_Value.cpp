// Problem: CF 2007 B - Index and Maximum Value
// https://codeforces.com/contest/2007/problem/B

/*
B. Index and Maximum Value
Algorithms/Techniques: Simulation with optimization using a single variable to track maximum value.

Time Complexity: O(n + m) per test case, where n is the size of the array and m is the number of operations.
Space Complexity: O(1) additional space (excluding input storage).

Each operation updates elements in the array based on range conditions.
Instead of modifying the entire array, we track only the maximum value 'x',
and update it directly with each operation if it falls within the range.
This avoids expensive array traversals for every operation.
*/

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false); // Disable sync with C stdio for faster input/output
  long t; // Number of test cases
  std::cin >> t;
  while (t--) { // Process each test case
    long n, m; // Length of array and number of operations
    std::cin >> n >> m;
    long x(0); // Track maximum value in the array
    for (long p = 0; p < n; p++) { // Read array elements and compute initial maximum
      long a;
      std::cin >> a;
      x = (a > x ? a : x); // Update maximum value
    }
    while (m--) { // Process each operation
      char c; // Operation type: '+' or '-'
      long l, r; // Range limits
      std::cin >> c >> l >> r;
      if (l <= x && x <= r) { // If current maximum is in the range
        x += (c == '+') - (c == '-'); // Update maximum accordingly
      }
      std::cout << x << " "; // Output current maximum after this operation
    }
    std::cout << std::endl; // End of line for current test case
  }
}


// https://github.com/VaHiX/codeForces/