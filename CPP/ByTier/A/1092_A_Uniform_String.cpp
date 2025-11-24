// Problem: CF 1092 A - Uniform String
// https://codeforces.com/contest/1092/problem/A

/*
Purpose: This code solves the problem of constructing a string of length n using exactly k distinct lowercase letters ('a' to 'k'-th letter) such that the minimum frequency of any letter is maximized.

Algorithm/Techniques:
- Greedy approach: Distribute the letters cyclically to balance frequencies.
- For each position i in the string, assign the letter corresponding to (i % k) + 'a'.
- This ensures that each of the k letters appears as evenly as possible.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) excluding the output space.

*/
#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
      cout << char(i % k + 'a');  // Assign letters cyclically to balance frequencies
    cout << endl;
  }
}


// https://github.com/VaHiX/CodeForces/