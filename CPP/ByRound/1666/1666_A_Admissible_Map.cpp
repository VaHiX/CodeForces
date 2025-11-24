// Problem: CF 1666 A - Admissible Map
// https://codeforces.com/contest/1666/problem/A

/*
 * Admissible Map Problem
 * 
 * Purpose: Given a string composed of 'U', 'L', 'D', 'R' characters,
 *          count how many substrings of the string can be interpreted
 *          as valid descriptions of admissible maps (i.e., map graphs
 *          that form cycles).
 *
 * Algorithms/Techniques:
 * - Rolling hash technique with multiple base polynomials for efficient substring comparison
 * - Dynamic programming to precompute next positions for R/L and U/D directions
 * - Map-based grouping of substrings by their lengths and modular indices
 * - Complexity analysis using hashing + dynamic programming principles
 *
 * Time Complexity: O(N^2), where N is the length of input string.
 * Space Complexity: O(N), due to arrays and maps storing intermediate values.
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
typedef unsigned long long ull;
const int N = 20005, P = 13331;
const char ch[] = "LRUD";
int n, nxt[N], nxu[N], nnl[N];
string s;
map<int, vector<pr>> pos[N];
ull h[4][N], p[N], pre[N];

// Computes hash value for range [l, r] using precomputed powers
inline ull H(ull h[N], int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }

// Computes a combined hash value of two substrings
inline ull In(int l, int r) {
  return H(h[0], l + 1, r) * P + H(h[1], l, r - 1);
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> s, n = s.size(), s = " " + s; // Padding to make indexing easier
  p[0] = pre[0] = 1;
  for (int i = 1; i <= n; i++) {
    p[i] = p[i - 1] * P; // Powers of polynomial base
    pre[i] = (pre[i - 1] + p[i]); // Prefix sum of powers
  }
  // Compute hash values for each direction (L, R, U, D)
  for (int k : {0, 1, 2, 3})
    for (int i = 1; i <= n; i++)
      h[k][i] = h[k][i - 1] * P + (s[i] == ch[k]);
  ll ans = 0;
  // Initialize next pointers to default values
  nxt[n + 1] = nnl[n + 1] = nxu[n + 1] = n + 1;

  // Traverse the string backwards from n down to 1
  for (int i = n; i >= 1; i--) {
    // Handle R-L transition: they cancel out in direction, use next valid position
    if (i == n || s[i] != 'R' || s[i + 1] != 'L')
      nxt[i] = i;
    else
      nxt[i] = nxt[i + 2];

    // Track nearest U upward
    if (s[i] == 'U')
      nxu[i] = i;
    else
      nxu[i] = nxu[i + 1];

    // Track nearest L to the left
    if (s[i] == 'L')
      nnl[i] = nnl[i + 1];
    else
      nnl[i] = i;

    ans += (nxt[i] - i) / 2; // Count valid pairs of R-L transitions
    int j = nxt[i], k = nxu[j];
    auto add = [&](int len, int s) {
      auto CheckTop = [&](int l, int r) {
        return H(h[2], l + len, r + len) + In(l, r) == pre[len - 1];
      };
      if (CheckTop(i, i + len - 1))
        pos[len][i % len].push_back({i, s}); // Push indices for further processing
    };

    if (j <= n && k <= n) {
      if (s[j] == 'R')
        add(k - j, j);
      if (s[j] == 'D')
        add(k - nnl[j + 1] + 1, j);
    }
  }

  // Iterate over possible lengths of valid substrings
  for (int len = 1; len <= n; len++) {
    for (auto [r, vc] : pos[len]) {
      int be = r ? r : len, m = (n - be + 1) / len;
      auto id = [&](int i) { return (i - be) / len; }; // Index mapping
      sort(vc.begin(), vc.end(), [&](pr x, pr y) {
        return max(id(x.fi) + 1, id(x.se)) > max(id(y.fi) + 1, id(y.se));
      });
      auto CheckMid = [&](int l, int r) {
        return H(h[3], l - len, r - len) + H(h[2], l + len, r + len) +
                   In(l, r) ==
               pre[len - 1];
      };
      auto CheckEnd = [&](int l, int r) {
        return H(h[3], l - len, r - len) + In(l, r) == pre[len - 1];
      };
      int i = m - 1, res = 0;
      for (auto [l, s] : vc) {
        int ix = max(id(l) + 1, id(s));
        for (; i >= ix; i--) {
          int L = be + i * len, R = be + (i + 1) * len - 1;
          if (!CheckMid(L, R))
            res = 0;
          if (CheckEnd(L, R))
            res++;
        }
        ans += res;
      }
    }
  }

  cout << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/codeForces/