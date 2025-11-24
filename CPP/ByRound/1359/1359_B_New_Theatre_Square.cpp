// Problem: CF 1359 B - New Theatre Square
// https://codeforces.com/contest/1359/problem/B

#include <iostream>
#include <string>

using namespace std;
int t, n, m, x, y, a, k;
string s;
int main() {
  for (cin >> t; t--;) {
    cin >> n >> m >> x >> y;
    k = 2 * x;        // Calculate cost of two 1x1 tiles
    a = 0;            // Initialize total cost
    while (n--) {
      cin >> s;
      for (int i = 0; i < m; i++) {
        if (s[i] == '.' && s[i + 1] == '.' && k > y)
          a += y, i++;  // Use 1x2 tile if cheaper than two 1x1 tiles
        else {
          if (s[i] == '.')
            a += x;     // Use 1x1 tile for single white square
        }
      }
    }
    cout << a << endl;
  }
}


// https://github.com/VaHiX/codeForces/