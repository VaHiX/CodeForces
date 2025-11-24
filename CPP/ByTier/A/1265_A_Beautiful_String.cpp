// Problem: CF 1265 A - Beautiful String
// https://codeforces.com/contest/1265/problem/A

/*
 * Problem: Beautiful String
 * 
 * Algorithm/Techniques: Greedy approach
 * 
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1) excluding the input and output storage
 * 
 * Approach:
 * - For each '?' character, we greedily assign it a character that:
 *   1. Is different from the previous character
 *   2. Is different from the next character (if it exists)
 * - If we cannot assign a valid character to a '?', we mark the string as impossible.
 * - The algorithm ensures no two consecutive characters are equal.
 * 
 * Note: The code uses ASCII values for characters ('a'=97, 'b'=98, 'c'=99)
 * and manipulates them to avoid consecutive duplicates.
 */

#include <iostream>
#include <string>

using namespace std;
int i, p, t;
string s;
int main() {
  for (cin >> t; t--;) {
    for (cin >> s, i = p = 0; s[i]; i++)
      if (s[i] > 96 & s[i] == s[i + 1])  // Check if current char is same as next
        p = 1;                           // Mark as impossible
      else if (s[i] < 96)                // If current char is '?'
        s[i] = i ? s[i - 1] % 3 + 97 : 97,  // Assign char based on previous, or 'a' if first
        s[i] == s[i + 1] ? s[i] = s[i] % 3 + 97 : 0;  // If assigned char equals next, adjust
    cout << (p ? "-1" : s) << endl;    // Output result
  }
}


// https://github.com/VaHiX/CodeForces/