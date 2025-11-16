// Problem: CF 1999 D - Slavic's Exam
// https://codeforces.com/contest/1999/problem/D

/*
Purpose: This code solves the problem of making a string `t` a subsequence of string `s` by replacing '?' characters in `s` with lowercase letters. 
         It checks if it's possible to form `t` as a subsequence of `s` by greedily assigning characters from `t` to '?' positions.

Algorithms/Techniques:
- Greedy Algorithm: Assign characters from `t` to '?' in `s` whenever possible.
- Two-pointer technique: Use `trot` to track progress in `t` and match characters in `s`.

Time Complexity: O(|s| + |t|) per test case, where |s| and |t| are the lengths of strings `s` and `t`.
Space Complexity: O(1) extra space excluding input/output storage.

*/
#include <iostream>
#include <string>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int q;
  cin >> q;
  while (q--) {
    string s, t;
    cin >> s >> t;
    int trot = 0; // Pointer to track which character in t we are trying to match
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '?') {
        // If we still have characters in t to match, assign the next one
        if (trot < t.size()) {
          s[i] = t[trot];
        } else {
          // Otherwise, assign 'a' to avoid violating the subsequence condition
          s[i] = 'a';
        }
      }
      // If current character in s matches the current target character in t, advance trot
      if (s[i] == t[trot])
        trot++;
    }
    // If we matched all characters in t, output YES and the modified string
    if (trot == t.size())
      cout << "YES \n" << s;
    else
      cout << "NO";
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/