// Problem: CF 1499 E - Chaotic Merge
// https://codeforces.com/contest/1499/problem/E

#include <iostream>
#include <string>
using namespace std;
#define For(i, l, r) for (int i = l; i <= r; i++)
#define P 998244353
#define MAXN 1001
int N, M, f[MAXN][MAXN][2], x[MAXN], y[MAXN], ans;
string a, b;
void upd(int &x, int y) { x = (x + y) % P; }
int main() {
  cin >> a >> b, N = a.length(), M = b.length(), a = " " + a, b = " " + b;
  // Precompute x[i]: number of ways to merge first i characters of a such that the last character is different from the previous one
  For(i, 1, N) x[i] = (a[i] != a[i - 1]) * x[i - 1] + 1;
  // Precompute y[i]: number of ways to merge first i characters of b such that the last character is different from the previous one
  For(i, 1, M) y[i] = (b[i] != b[i - 1]) * y[i - 1] + 1;
  // Dynamic programming over all substrings
  For(i, 1, N) For(j, 1, M) {
    // If current character in a is different from previous, we can extend previous state where last character was from a
    if (a[i] != a[i - 1])
      upd(f[i][j][0], f[i - 1][j][0]);
    // If current character in b is different from previous, we can extend previous state where last character was from b
    if (b[j] != b[j - 1])
      upd(f[i][j][1], f[i][j - 1][1]);
    // If characters from a and b are different, we can merge them
    if (a[i] != b[j])
      // Update the states by appending from a or b respectively
      upd(f[i][j][0], f[i - 1][j][1] + y[j]),
          upd(f[i][j][1], f[i][j - 1][0] + x[i]);
  }
  // Sum all valid sequences
  For(i, 1, N) For(j, 1, M) upd(ans, f[i][j][0]), upd(ans, f[i][j][1]);
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/