// Problem: CF 1678 B2 - Tokitsukaze and Good 01-String (hard version)
// https://codeforces.com/contest/1678/problem/B2

/*
Code Purpose:
This code solves the problem of making a binary string "good" by minimizing the number of operations (changing bits) and also minimizing the number of contiguous subsegments after the transformation. A string is good if all subsegments have even lengths and consist of the same character.

Approach:
1. The string is processed in pairs of characters (since we check pairs to determine if a subsegment can be extended).
2. If two adjacent characters in a pair are different, it means a change is needed to make them same (incrementing operation count `x`).
3. If characters are same, we track the length of continuous segments (by incrementing `y` when a new segment begins).
4. The minimum number of operations is `x`.
5. The minimum number of subsegments is `max(y, 1)` (we need at least 1 subsegment).

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) as only a few variables are used.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    int x = 0, y = 0, l = -1;
    for (int i = 0; i < n; i += 2) {
      if (s[i] != s[i + 1]) {
        x++;  // Increment operations count if pair is different
      } else {
        if (l != s[i]) {
          y++;  // Increment subsegment count if new segment starts
        }
        l = s[i];  // Mark current character as last seen
      }
    }
    cout << x << " " << max(y, 1) << endl;  // Output min operations and subsegments
  }
}


// https://github.com/VaHiX/CodeForces/