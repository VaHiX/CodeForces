// Problem: CF 1280 A - Cut and Paste
// https://codeforces.com/contest/1280/problem/A

/*
Algorithm: String Simulation with Optimized Length Calculation
Time Complexity: O(x * |s|) where x <= 1e6 and |s| <= 500
Space Complexity: O(|s|) for storing the string and auxiliary variables

This code simulates a process on a string with a cursor, clipboard, and three operations:
- Move: move cursor one step right
- Cut: split string at cursor, left part becomes string, right part becomes clipboard
- Paste: append clipboard to string, cursor position is incremented accordingly

The simulation is optimized by:
1. Tracking only the length of the string instead of the full string
2. Using modular arithmetic to handle large numbers
3. Avoiding unnecessary string copies when possible

Key variables:
- x: target cursor position to stop at
- c[]: input string representing the operations
- l1: current length of the string
- l2: current length of the clipboard
- T: number of test cases
*/
#include <stdio.h>
#include <string.h>

const int N = 1e6 + 5, mo = 1e9 + 7;
int T, x, i, j, l1, l2;
char c[N];
int main() {
  for (scanf("%d", &T); T--;) {
    scanf("%d%s", &x, c + 1);
    l1 = l2 = strlen(c + 1);
    for (i = 1; i <= x; ++i) {
      int dl = l1 - i;
      l1 = (l1 + 1ll * (dl + mo) * (c[i] - '0' - 1)) % mo;
      if (l2 <= x + 1)
        for (j = 0; j < (c[i] - '0' - 1) * dl && l2 < x + 1; ++j)
          ++l2, c[l2] = c[l2 - dl];
    }
    printf("%d\n", l1);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/