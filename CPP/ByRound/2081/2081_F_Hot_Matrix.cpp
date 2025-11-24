// Problem: CF 2081 F - Hot Matrix
// https://codeforces.com/contest/2081/problem/F

/*
F. Hot Matrix
Algorithms/Techniques: Construction algorithm using specific permutation patterns and modular arithmetic.

Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) due to storing the matrix

The code constructs a "hot matrix" based on specific rules for valid n values.
It only works when n is odd or equal to 1. For even n > 1, no such matrix exists.
The algorithm uses two arrays a and b that help in generating the matrix rows
and columns in a way that satisfies all given constraints.

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    if (n % 2 == 0 || n == 1) { // Only valid for odd n or n=1
      cout << "YES\n";
      vector<int> a(n), b(n); // Two arrays used to build the matrix structure
      for (int i = 1; i < n; i++) { // Fill arrays a and b based on pattern
        if (i & 1) // If i is odd
          a[i] = (i + 1) / 2;
        else // If i is even
          a[i] = n - i / 2;
        b[a[i]] = i; // Build reverse mapping
      }
      for (int i = 0; i < n; i++) { // Generate and print matrix rows
        for (int j = 0; j < n; j++) {
          cout << b[(a[i] + a[j]) % n] << " \n"[j + 1 == n]; // Output element with proper spacing
        }
      }
    } else
      cout << "NO\n"; // Even n > 1 has no solution
  }
}


// https://github.com/VaHiX/codeForces/