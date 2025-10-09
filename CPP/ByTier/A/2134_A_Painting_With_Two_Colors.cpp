// Problem: CF 2134 A - Painting With Two Colors
// https://codeforces.com/contest/2134/problem/A

/*
Problem: Painting With Two Colors
Task: Determine if it's possible to choose positions x and y such that the final painted grid is symmetric.
Algorithms/Techniques: Mathematical analysis of symmetry and overlap conditions.

Time Complexity: O(1) per test case - constant time operations.
Space Complexity: O(1) - only using a fixed number of variables.

The solution relies on:
- Checking parity conditions for n+a to ensure valid distribution
- Ensuring that the difference between b and a (or 0) is even to maintain symmetry
*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
int t;
int main() {
  cin >> t;
  while (t--) {
    int n, a, b;
    cin >> n >> a >> b;
    swap(a, b); // Swap a and b to make processing easier
    if ((n + a) % 2 == 0 && (max(b - a, 0)) % 2 == 0)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}


// https://github.com/VaHiX/codeForces/