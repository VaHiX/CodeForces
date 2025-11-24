// Problem: CF 1705 C - Mark and His Unfinished Essay
// https://codeforces.com/contest/1705/problem/C

/*
Purpose: Solve the problem of finding the k-th character in a string after multiple copy-paste operations.
         The solution uses a reverse approach to efficiently determine which original character contributes to the k-th position.

Algorithms/Techniques:
- Reverse simulation to find the source of a query character
- Precompute cumulative lengths of the string after each operation to enable binary search or direct lookup

Time Complexity: O(c * q + n) where c is number of operations and q is number of queries
Space Complexity: O(c) for storing lengths and operations

*/

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, c, q;
    cin >> n >> c >> q;
    string s;
    cin >> s;
    long long l[c + 1], r[c + 1], len[c + 2]; // l[r] stores the range of copy-paste, len stores cumulative length
    len[0] = n;  // Initial length of string
    for (int i = 1; i <= c; i++) {
      cin >> l[i] >> r[i];  // Read the range for copy-paste operation
      len[i] = len[i - 1] + r[i] - l[i] + 1;  // Update cumulative length after this operation
    }
    while (q--) {
      long long k;
      cin >> k;
      // Reverse simulation: Find the original position of k-th character
      for (int i = c - 1; i >= 0; i--) {
        if (k > len[i]) {
          // If k is beyond current length, it's from the paste operation
          k = l[i + 1] + (k - len[i] - 1);  // Adjust k to original string position
        }
      }
      assert(k <= n); // Ensure k falls within the original string bounds
      cout << s[k - 1] << endl; // Output the character at position k (1-indexed)
    }
  }
}


// https://github.com/VaHiX/CodeForces/