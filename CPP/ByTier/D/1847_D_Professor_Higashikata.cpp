// Problem: CF 1847 D - Professor Higashikata
// https://codeforces.com/contest/1847/problem/D

/*
 * Problem: Professor Higashikata
 * 
 * Purpose: Given a binary string s, m substrings defined by intervals [l_i, r_i],
 *          and q queries to flip bits in s. For each query, compute the minimum
 *          number of swaps needed to make the concatenated string t(s) lexicographically
 *          largest possible.
 * 
 * Algorithm:
 * - Use greedy approach to identify which positions in the union of substrings
 *   should be '1' for maximum lexicographical value.
 * - For each update, maintain counters and flags to track the minimum number of
 *   operations needed.
 * 
 * Time Complexity: O(n + m + q)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Interval merging and tracking of unique positions
 * - Greedy optimization for lexicographically maximum string
 * - Efficient bit flipping and counting
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define MOD 1000000007
#define display(a)                                                             \
  for (auto i : a)                                                             \
    cout << i << " ";
#define nl '\n'
#define cdiv(a, b) (a) / (b) + ((a) % (b) > 0)
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL)
#define ll long long int
#define debug(n) cout << #n << " : " << n << '\n';
#define debug2(n1, n2)                                                         \
  cout << #n1 << " : " << n1 << "  " << #n2 << " : " << n2 << '\n';
void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  string s;
  cin >> s;
  vector<pair<int, int>> a(m);
  for (int i = 0; i < m; i++) {
    cin >> a[i].first >> a[i].second;
  }
  vector<int> sa;
  vector<int> vis(n + 1, 0);
  for (int i = 0; i < m; i++) {
    int j = a[i].first;
    while (j <= a[i].second) {
      if (vis[j] == 0) {
        vis[j] = a[i].second;
        sa.push_back(j);
      } else {
        j = vis[j];
      }
      j++;
    }
  }
  int cn1 = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      cn1++;
    }
  }
  int ans = 0;
  int nn = sa.size();
  vector<int> qvis(n + 1, 0);
  for (int i = 0; i < min(cn1, nn); i++) {
    qvis[sa[i]] = 1;
    if (s[sa[i] - 1] == '0') {
      ans++;
    }
  }
  for (int i = 0; i < q; i++) {
    int x;
    cin >> x;
    if (cn1 > nn) {
      // Case where current number of 1s exceeds available positions
      if (s[x - 1] == '0') {
        cn1++;
        if (qvis[x] == 1) {
          ans--;
        }
      } else {
        cn1--;
        if (qvis[x] == 1) {
          ans++;
        }
      }
    } else {
      // Case where current number of 1s is less than or equal to available positions
      if (s[x - 1] == '1') {
        // Flipping a '1' to '0'
        if (s[sa[cn1 - 1] - 1] == '0') {
          ans--;
        }
        qvis[sa[cn1 - 1]] = 0;
        cn1--;
        if (qvis[x] == 1) {
          ans++;
        }
      } else {
        // Flipping a '0' to '1'
        cn1++;
        if (cn1 <= nn) {
          if (s[sa[cn1 - 1] - 1] == '0') {
            ans++;
          }
          qvis[sa[cn1 - 1]] = 1;
        }
        if (qvis[x] == 1) {
          ans--;
        }
      }
    }
    s[x - 1] = s[x - 1] == '1' ? '0' : '1';
    cout << ans << nl;
  }
}
int main() {
  fast_io;
  int t = 1;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/