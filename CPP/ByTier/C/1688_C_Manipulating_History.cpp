// Problem: CF 1688 C - Manipulating History
// https://codeforces.com/contest/1688/problem/C

/*
Code Purpose:
This code determines the initial string of Gensokyo by exploiting the fact that each operation replaces a substring with another, and the sequence of operations is shuffled. The key insight is that the XOR of all characters in the operation strings (t_i) will cancel out all characters except the initial character of the original string. This works because each character in the original string appears an equal number of times in the t_i strings (once as a substring, once in the replacement), except for the root character which only appears in t_1.

Algorithms/Techniques:
- XOR operation to isolate the initial character
- Observing that t_1 (the first operation's first string) must be a substring of the original string and the replacement of it must include the initial character

Time Complexity: O(total length of all input strings)
Space Complexity: O(1) - only using a single char variable for XOR operations

*/

#include <iostream>
#include <string>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    n = 2 * n + 1;  // Total number of strings in t (2*n operations + 1 final string)
    char c = 0;     // Initialize XOR accumulator
    while (n--) {
      string s;
      cin >> s;
      for (auto x : s)
        c = c ^ x;  // XOR each character to cancel out pairs
    }
    cout << c << '\n';  // The remaining character is the initial one
  }
}


// https://github.com/VaHiX/CodeForces/