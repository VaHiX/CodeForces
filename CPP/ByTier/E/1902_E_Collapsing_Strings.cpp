// Problem: CF 1902 E - Collapsing Strings
// https://codeforces.com/contest/1902/problem/E

/*
 * Problem: E. Collapsing Strings
 * Algorithm: Trie-based optimization for collapsing string lengths.
 * 
 * Approach:
 * - Build a trie from all input strings to efficiently check prefixes/suffixes.
 * - For each string, reverse it and traverse the trie to find common suffixes.
 * - Use inclusion-exclusion principle: total sum = 2*n*sum(len) - 2*sum(common_lengths)
 * 
 * Time Complexity: O(sum of string lengths)
 * Space Complexity: O(sum of string lengths)
 */

#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define ull unsigned long long
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define fi first
#define se second
#define all(x) x.begin(), x.end()
const int maxn = 1e6 + 10;
const int maxm = 4e5 + 10;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-7;
const double PI = acos(-1.0);
int tot = 1;
int trie[maxn][26];
int cnt[maxn];

void solve() {
  int n;
  cin >> n;
  vector<string> s(n);
  ll ans = 0;
  // Build trie and calculate initial total length sum
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
    ans += s[i].size(); // Add string length to answer
    int p = 1;
    // Insert string into trie and maintain count of nodes
    for (auto c : s[i]) {
      int &q = trie[p][c - 'a'];
      if (!q) {
        q = ++tot;  // Create new node if not exists
      }
      p = q;
      cnt[p]++;   // Increment count of this node
    }
  }
  // Multiply by 2*n as every pair contributes twice
  ans *= 2 * n;
  // Traverse reversed strings to find overlaps
  for (int i = 0; i < n; i++) {
    reverse(s[i].begin(), s[i].end()); // Reverse string to check suffixes
    int p = 1;
    for (auto c : s[i]) {
      int &q = trie[p][c - 'a'];
      if (!q)  // Break if no overlap
        break;
      p = q;
      ans -= 2 * cnt[p];  // Subtract the overlapping contribution
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/