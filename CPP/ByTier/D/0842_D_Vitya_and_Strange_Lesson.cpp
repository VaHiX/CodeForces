/*
 * Problem URL : https://codeforces.com/problemset/problem/842/D
 * Submit Date : 2025-08-15
 */

#include <iostream>
using namespace std;
typedef unsigned int unt;

constexpr unt off = 1u << 19u;
unt s[off << 1u];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  unt n, m;
  cin >> n >> m;
  while (n--) {
    unt a;
    cin >> a;
    a |= off;
    if (s[a])
      continue;
    while (a) {
      s[a]++;
      a >>= 1u;
    }
  }
  unt x = 0u;
  while (m--) {
    unt xx;
    cin >> xx;
    x ^= xx;
    unt i = 1u;
    for (unt b = off; b >>= 1u;) {
      i <<= 1u;
      if (x & b)
        i |= 1u;
      if (s[i] == b)
        i ^= 1u;
    }
    cout << (i & ~off ^ x) << '\n';
  }
}