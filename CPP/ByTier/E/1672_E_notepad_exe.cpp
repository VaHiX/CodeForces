// Problem: CF 1672 E - notepad.exe
// https://codeforces.com/contest/1672/problem/E
 
/*
Algorithm: Binary search to find minimum width w such that h_w != 0, then use queries to determine optimal area.
Time Complexity: O(n log W) where W is up to 1e9, and we do at most O(n) queries.
Space Complexity: O(1), only using a few variables.
 
The problem involves finding the minimum area of a text editor given that words are split into lines
optimally for a given width w. The height h_w represents the number of lines needed for a valid layout
when width is w. We are to minimize w * h_w for valid w (where h_w != 0).
Steps:
1. Binary search for minimum width w where h_w > 0.
2. Determine how much the area can be reduced by trying different widths.
3. Output minimum area.
*/
 
#include <iostream>
#include <algorithm>
 
#define q(y)                                                                   \
  cout << "? " << y << endl;                                                   \
  cin >> q;
using namespace std;
int n, q, a, i, l = 1, r = 4000000;
int main() {
  cin >> n;
  while (l != r) {
    i = (l + r) / 2;
    q(i)(q - 1) ? l = i + 1 : r = i;
  }
  for (; n > 1; n--) {
    q(r / n) if (q == n) a = max(r % n, a);
  }
  cout << "! " << r - a << endl;
}
 
 
// https://github.com/VaHiX/CodeForces/