// Problem: CF 2126 E - G-C-D, Unlucky!
// https://codeforces.com/contest/2126/problem/E

/*
E. G-C-D, Unlucky!
Problem: Determine whether there exists an array 'a' such that given prefix GCD array 'p' and suffix GCD array 's' can be derived from it.

Algorithms/Techniques:
- GCD properties and validation of prefix/suffix arrays
- Modular arithmetic checks for divisibility
- Greedy validation of constraints

Time Complexity: O(n * log(max(a[i]))) per test case, where n is the length of arrays.
Space Complexity: O(n) for storing input arrays.

*/

#include <algorithm>
#include <iostream>
#include <numeric> // Required for __gcd

using namespace std;
const int N = 2e5 + 5; // Maximum size for arrays
int t, n, m, a[N], b[N], f; // f is flag to indicate validity

int main() {
  cin >> t; // Read number of test cases
  while (t--) { // Process each test case
    cin >> n; // Read size of arrays
    f = 1; // Initialize flag to 1 (valid)
    
    for (int i = 1; i <= n; i++)
      cin >> a[i]; // Read prefix GCD array
    
    for (int i = 1; i <= n; i++)
      cin >> b[i]; // Read suffix GCD array
    
    // Check if last element of prefix GCD equals first element of suffix GCD
    if (a[n] != b[1])
      f = 0;
    
    // Validate that prefix GCDs are decreasing (each divides next)
    for (int i = 1; i < n; i++) {
      if (a[i] % a[i + 1] != 0) // If a[i] is not divisible by a[i+1], invalid
        f = 0;
      if (b[i + 1] % b[i] != 0) // If b[i+1] is not divisible by b[i], invalid
        f = 0;
    }
    
    // Validate GCD constraints between prefix and suffix arrays
    for (int i = 1; i < n; i++) {
      if (__gcd(a[i], b[i + 1]) != a[n]) // Each pair must have GCD equal to last element of prefix array
        f = 0;
    }
    
    if (f == 0)
      cout << "NO\n"; // If flag is 0, output NO
    else
      cout << "YES\n"; // Otherwise, output YES
  }
  return 0; // End of program
}


// https://github.com/VaHiX/codeForces/