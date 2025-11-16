// Problem: CF 1503 A - Balance the Bits
// https://codeforces.com/contest/1503/problem/A

#include <stddef.h>
#include <iostream>
#include <string>

using namespace std;
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, n;
  string s, a, b;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    int cnt = 0, k = 0;
    for (char i : s)
      cnt += i == '1';
    if (cnt & 1 || s[0] == '0' || s.back() == '0') {
      cout << "NO\n";
      continue;
    }
    a = b = "";
    bool flip = false;
    for (char i : s) {
      if (i == '1') {
        // For '1' in s, we assign '(' to 'a' if we are in first half of '1's, otherwise ')'
        a += k << 1 < cnt ? '(' : ')';
        // Assign same bracket as 'a' to 'b'
        b += a.back();
        k++;
      } else {
        // For '0' in s, we assign opposite brackets to 'a' and 'b'
        a += flip ? '(' : ')';
        b += flip ? ')' : '(';
        flip = !flip;
      }
    }
    cout << "YES\n" << a << '\n' << b << '\n';
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/