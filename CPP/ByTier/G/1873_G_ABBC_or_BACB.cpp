// Problem: CF 1873 G - ABBC or BACB
// https://codeforces.com/contest/1873/problem/G

/*
Purpose:
This problem asks to maximize the number of coins obtained by transforming substrings "AB" to "BC" or "BA" to "CB".
The key insight is that each such transformation consumes one "A" and one "B", so the maximum number of operations is bounded
by the minimum number of A's and B's in the string, but with some exceptions when patterns make it impossible.

Algorithms/Techniques:
- Greedy approach by observing the transformation rules
- Counting characters and handling edge cases where no operations are possible
- Special handling for strings that start and end with 'A' and have all middle characters as 'B'

Time Complexity: O(n) where n is the length of the string, due to single pass through the string.
Space Complexity: O(1) as we use only a constant amount of extra space (excluding input storage).

*/
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
using ll = long long;
const int N = 2e5 + 5;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int idx, ne[N], e[N], h[N];
void add(int a, int b) {
  e[idx] = b;
  ne[idx] = h[a];
  h[a] = idx++;
}
void solve() {
  string s;
  cin >> s;
  int n = s.size();
  int cnta = count(s.begin(), s.end(), 'A'), // Count total number of A
      cntb = count(s.begin(), s.end(), 'B'); // Count total number of B
  if (cnta == 0 || cntb == 0) { // If all characters are same, no operation possible
    cout << 0 << '\n';
    return;
  }
  bool fg = 1;
  if (s[0] == 'A' && s[n - 1] == 'A') { // If string starts and ends with 'A'
    fg = 0;
    for (int i = 1; i < n - 1; i++) {
      if (s[i] == 'B' && s[i + 1] == 'B') // Check if there is a consecutive BB in middle
        fg = 1;
    }
  }
  if (!fg) { // If the special case is true, adjust count
    int ans = 1e9;
    int t = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == 'A')
        t++;
      else {
        ans = min(ans, t); // Find minimum consecutive A's before a B
        t = 0;
      }
    }
    if (t) {
      ans = min(ans, t); // Handle final sequence of A's
    }
    cnta -= ans; // Decrease A count by minimum consecutive A's
  }
  cout << cnta << '\n';
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  std::cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/