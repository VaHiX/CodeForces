// Problem: CF 1907 C - Removal of Unattractive Pairs
// https://codeforces.com/contest/1907/problem/C

/*
C. Removal of Unattractive Pairs
Purpose: Given a string, we can remove adjacent pairs of different characters any number of times.
         The goal is to find the minimum possible length after all possible operations.
Algorithm: 
    - Count frequency of each character in the string.
    - Find maximum frequency of any single character (mx).
    - The minimum length is max(n % 2, 2 * mx - n).
      This accounts for:
        - If n is odd, at least one character must remain.
        - Otherwise, if we have a character that appears too many times,
          some will be left over after pairing.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) since there are at most 26 lowercase letters in the map.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> m; // Count frequency of each character
    int mx = 0;       // Track maximum frequency
    for (auto x : s) {
      m[x]++;
      mx = max(mx, m[x]); // Update maximum frequency
    }
    cout << max(n % 2, 2 * mx - n) << endl; // Compute and output result
  }
}


// https://github.com/VaHiX/codeForces/