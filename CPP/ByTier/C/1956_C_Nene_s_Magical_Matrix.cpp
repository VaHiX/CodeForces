// Problem: CF 1956 C - Nene's Magical Matrix
// https://codeforces.com/contest/1956/problem/C

/*
Code Purpose:
This code solves the problem of maximizing the sum of a matrix filled with zeroes by performing specific operations. 
The operations allow setting rows or columns of the matrix to a given permutation of integers from 1 to n.
The goal is to achieve the maximum possible sum with at most 2*n operations.

Algorithms/Techniques:
- Greedy approach to maximize sum by assigning optimal permutations
- Uses mathematical formula to precompute maximum sum for given n
- Constructs operations in a specific pattern to achieve the maximum sum efficiently

Time Complexity: O(n^2) - due to the loop that computes the sum and the string construction loops.
Space Complexity: O(n) - for storing string representations of permutations.
*/

#include <iostream>
#include <string>

using namespace std;

void solve() {
  long long int n;
  cin >> n;
  if (n > 1) {
    long long int sum = 0;
    // Compute the maximum possible sum using the derived formula
    for (long long int i = 1; i <= n; i++) {
      sum += i * (2 * i - 1);
    }
    cout << sum << " " << 2 * n << endl;
    string s = "", s1 = "";
    // Construct descending permutation string
    for (long long int i = n; i > 0; i--) {
      s = s + to_string(i) + " ";
    }
    // Construct ascending permutation string
    for (long long int i = 1; i <= n; i++) {
      s1 = s1 + to_string(i) + " ";
    }
    // First operation: set first row with ascending permutation
    cout << 1 << " " << 1 << " " << s1 << endl;
    // Second operation: set first column with descending permutation
    cout << 2 << " " << 1 << " " << s << endl;
    // Remaining operations: set rows and columns with descending permutation
    for (long long int i = 2; i <= n; i++) {
      cout << 1 << " " << i << " " << s << endl;
      cout << 2 << " " << i << " " << s << endl;
    }
  }
  if (n == 1) {
    // Special case for n=1
    cout << 1 << " " << 1 << endl;
    cout << 1 << " " << 1 << " " << 1 << endl;
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/