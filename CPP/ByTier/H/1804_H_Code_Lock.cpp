// Problem: CF 1804 H - Code Lock
// https://codeforces.com/contest/1804/problem/H

// Problem: H. Code Lock
// Purpose: Find the optimal arrangement of letters on a circular lock to
// minimize
//          the time needed to input a given password. The solution uses dynamic
//          programming with bitmasks to enumerate permutations and calculate
//          costs.
//
// Algorithm:
// - Preprocess the transition costs between consecutive characters in the
// password.
// - Use bitmask DP to compute minimal cost of assigning letters to sectors.
// - Enumerate all valid assignments of letters to sectors in a way that
// minimizes
//   the total rotation and input time.
//
// Time Complexity: O(3^k * k * n)
// Space Complexity: O(2^k)
#include <iostream>
#include <stdio.h>
#include <time.h>

#define For(i, a, b) for (int i = a; i <= b; i++)
#define Rev(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
const int N = 1e5 + 5;
typedef long long ll;
struct Node {
  int x;
  ll y;
  Node &operator+=(const Node &nd) {
    if (nd.x < x)
      *this = nd;
    else if (nd.x == x)
      y += nd.y;
    return *this;
  }
};
char ss[N];
int m, n, all, cc[16][16], a[1 << 16];
Node f[1 << 16];
Node calc(int L, int R) {
  For(i, 0, all) f[i] = Node{int(1e9), 0};
  f[1 << (ss[1] - 'a')] = Node{a[L], 1};
  For(s, 0, all) {
    if (f[s].y == 0)
      continue;
    int s3 = s & L, s4 = s & R, s1 = L ^ s3, s2 = R ^ s4;
    Node tt = f[s];
    if ((m & 1) || !__builtin_parity(s))
      tt.x += a[s1 | s4];
    int T = __builtin_parity(s) ? s2 : s1;
    for (int i = T; i; i -= i & -i)
      f[s | (i & -i)] += tt;
  }
  return f[all];
}
signed main() {
  cin >> m >> n >> (ss + 1);
  all = (1 << m) - 1;
  For(i, 1, n - 1) cc[ss[i] - 'a'][ss[i + 1] - 'a']++;
  For(s, 0, all) {
    For(i, 0, m - 1) if (s >> i & 1) For(j, 0, m - 1) if (~s >> j & 1) a[s] +=
        cc[i][j] + cc[j][i];
  }
  Node ans{int(1e9), 0};
  For(s, 0, all) {
    if (__builtin_popcount(s) != (m + 1) / 2)
      continue;
    if (~s >> (ss[1] - 'a') & 1)
      continue;
    ans += calc(s, all ^ s);
  }
  if (m & 1)
    ans.x /= 2;
  cout << ans.x + n << ' ' << ans.y << '\n';
  return 0;
}

// https://github.com/VaHiX/CodeForces/