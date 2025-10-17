// Problem: CF 2050 E - Three Strings
// https://codeforces.com/contest/2050/problem/E

/*
E. Three Strings
Algorithms/Techniques: Dynamic Programming
Time Complexity: O(|a| * |b|), where |a| and |b| are lengths of strings a and b respectively.
Space Complexity: O(|a| * |b|), for the DP table f.

The problem involves finding the minimum number of character changes in string c,
which is formed by interleaving strings a and b, with some characters potentially altered.
We use dynamic programming to find the maximum number of matching characters
between the interleaved version of a and b and c. Then we subtract that from total length
to get the minimum number of changes.

*/
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1005;
char a[N], b[N], c[N * 2];
int f[N][N];

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> a + 1 >> b + 1 >> c + 1;
    int la = strlen(a + 1), lb = strlen(b + 1), mx = 0;
    for (int i = 1; i <= la + lb; i++) {
      for (int j = max(0, i - lb); j <= la && j <= i; j++) {
        // f[j][i - j] represents the maximum number of matches up to this point
        // when using j characters from a and (i-j) characters from b
        f[j][i - j] = 0;
        if (j > 0)
          // Take a character from a and update state accordingly
          f[j][i - j] = max(f[j][i - j], f[j - 1][i - j] + (a[j] == c[i]));
        if (i - j > 0)
          // Take a character from b and update state accordingly
          f[j][i - j] = max(f[j][i - j], f[j][i - j - 1] + (b[i - j] == c[i]));
      }
    }
    // Total characters minus maximum matches gives minimum changes needed
    cout << la + lb - f[la][lb] << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/