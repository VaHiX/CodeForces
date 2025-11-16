// Problem: CF 1728 D - Letter Picking
// https://codeforces.com/contest/1728/problem/D

/*
Purpose: Solve the letter picking game where Alice and Bob alternate picks from either end of a string,
         aiming to form lexicographically smallest strings. The game result depends on optimal play.
         Alice starts first. The winner is determined by comparing the final strings lexicographically.
         If strings are equal, it's a draw.

Algorithms/Techniques:
- Greedy strategy simulation
- Two-pointer technique to compare from both ends
- Special handling for equal characters at both ends
- Detecting if all remaining characters are the same

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) - only using a few variables, not counting input storage.
*/

#include <iostream>
#include <string>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    int l = 0, r = s.length() - 1;
    // Move pointers inward while characters at both ends are equal
    while (s[l] == s[r])
      l++, r--;
    bool dr = true; // Assume a draw initially
    // Check if all remaining characters are the same
    for (int i = l; i < r; i++, i++) // Increment by 2 for efficiency
      if (s[i] != s[i + 1])
        dr = false;
    // Output result: if all remaining are the same, it's a draw; otherwise, Alice wins
    cout << (dr ? "Draw" : "Alice") << endl;
  }
}


// https://github.com/VaHiX/CodeForces/