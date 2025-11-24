// Problem: CF 2072 F - Goodbye, Banker Life
// https://codeforces.com/contest/2072/problem/F

/*
F. Goodbye, Banker Life

The problem involves generating the n-th row of a special triangle where:
- The first row has one element k.
- Each subsequent row i has i elements.
- For row i and column j:
  - If j == 1: T[i][1] = T[i-1][1]
  - If j == i: T[i][j] = T[i-1][j-1]
  - Otherwise: T[i][j] = T[i-1][j-1] XOR T[i-1][j]

This pattern resembles Pascal's triangle with XOR operations instead of addition.
The key insight is that for any element (n, i), it's equal to k if i equals 0 or n, and 0 otherwise.

Algorithm:
  - For each test case:
    - Generate the n-th row.
    - Use the property that only first and last elements are k, rest are 0.
    
Time Complexity: O(n) per test case, due to looping from 0 to n-1.
Space Complexity: O(1) extra space (excluding output), as we do not store previous rows.

*/
#include <iostream>

using namespace std;
int main() {
  int T, n, k, i;
  for (cin >> T; T > 0; T--) {
    cin >> n >> k;
    n--; // Adjusting n to zero-indexed for easier loop handling
    for (i = 0; i <= n; i++) {
      if ((n & i) == i) // Check if i is a subset of n in binary representation (bitmask technique)
        cout << k << ' '; // If true, the value is k (first and last elements are k)
      else
        cout << "0 "; // Else, it's 0 due to properties of XOR triangle
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/