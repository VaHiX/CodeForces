/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/E
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
string s;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, q;
  cin >> t;
  while (t--) {
    int b = 0, c = 0, bc = 0, cb = 0, crb = 0, crc = 0;
    cin >> n >> q;
    cin >> s;
    char x, y;
    for (int i = 1; i <= q; ++i) {
      cin >> x >> y;
      if (x == 'b' && y == 'c')
        bc++;
      if (x == 'c' && y == 'b')
        cb++;
      if (y == 'a')
        if (x == 'b') {
          if (cb)
            cb--, crc++;
          else
            b++;
        } else if (x == 'c') {
          if (bc)
            bc--, crb++;
          else
            c++;
        }
    }
    for (char &ch : s) {
      if (ch == 'b') {
        if (b)
          b--, ch = 'a';
        else if (crc)
          crc--, cb++, ch = 'a';
        else if (crb)
          crb--, ch = 'a';
      }
      if (ch == 'c') {
        if (c)
          c--, ch = 'a';
        else if (crb)
          crb--, bc++, ch = 'a';
        else if (crc)
          crc--, ch = 'a';
        else if (cb)
          cb--, ch = 'b';
      }
    }
    cout << s << '\n';
  }
  return 0;
}