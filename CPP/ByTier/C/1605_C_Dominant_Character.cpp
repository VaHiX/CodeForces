// Problem: CF 1605 C - Dominant Character
// https://codeforces.com/contest/1605/problem/C

/*
 * Problem: Find the shortest substring where 'a' occurs strictly more times than both 'b' and 'c'
 * Algorithm: Brute force approach with pre-defined patterns
 * Time Complexity: O(n) where n is the length of string s, as we check at most 7 predefined substrings
 * Space Complexity: O(1) as we use only a constant amount of extra space
 * 
 * The approach is based on observing that the minimum valid substring must be one of these 7 patterns:
 * "aa", "aba", "aca", "abca", "acba", "abbacca", "accabba"
 * These patterns cover all possible minimal configurations where 'a' > 'b' and 'a' > 'c'
 * We check if any of these patterns exist in the input string and return the length of the first match
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, i;
    cin >> n;
    string s,
        ans[7] = {"aa", "aba", "aca", "abca", "acba", "abbacca", "accabba"};
    cin >> s;
    int res = -1;
    for (int i = 0; i < 7; i++) {
      // Check if current pattern exists in the string
      if (s.find(ans[i]) != -1) {
        res = ans[i].length();  // Store length of first matching pattern
        break;  // Stop as we want the smallest length
      }
    }
    cout << res << endl;
  }
}


// https://github.com/VaHiX/CodeForces/