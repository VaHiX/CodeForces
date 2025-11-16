// Problem: CF 1005 B - Delete from the Left
// https://codeforces.com/contest/1005/problem/B

/*
B. Delete from the Left
Algorithm: Find the longest common suffix of two strings.
Time Complexity: O(min(|s|, |t|)) where |s| and |t| are lengths of the strings.
Space Complexity: O(1)

Approach:
- Start from the end of both strings and find the longest common suffix.
- The number of moves needed equals to (length of s - length of common prefix) + (length of t - length of common prefix)
- This is equivalent to total length minus twice the length of the common suffix.
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  string f, s;
  cin >> f >> s;
  int i = f.size() - 1, j = s.size() - 1;
  // Traverse from the end to find common suffix
  while (i >= 0 && j >= 0 && f[i] == s[j]) {
    i--;
    j--;
  }
  // i+1 and j+1 represent lengths of common prefix from the start
  cout << i + j + 2; // Total moves = (len_f - len_common_prefix) + (len_t - len_common_prefix)
}


// https://github.com/VaHiX/codeForces/