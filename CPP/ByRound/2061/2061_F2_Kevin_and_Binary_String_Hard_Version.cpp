// Problem: CF 2061 F2 - Kevin and Binary String (Hard Version)
// https://codeforces.com/contest/2061/problem/F2

/*
Algorithm: The problem involves transforming string s into string t using adjacent block swaps. 
Key insights:
1. Blocks are maximal substrings of identical characters.
2. We can only swap adjacent blocks.
3. We use dynamic programming with segment trees to efficiently find minimum operations.
4. For each position in the transformed string, we calculate how many swaps are needed to move blocks into correct positions.

Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

Approach:
- Preprocess strings to count character occurrences and find next/previous positions of characters in target string.
- Identify blocks in the source string.
- Use dynamic programming with segment trees to track minimum operations needed to bring blocks to correct positions.
- The final answer is derived from the DP values adjusted for block swapping logic.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define xx first
#define yy second
using namespace std;
long long int typedef li;
const int mod = 1000000007;
int pres[2][400005]; // prefix counts for characters
int pret[2][400005]; // prefix counts for target string
int nxt[2][400005];  // next occurrence positions
int prv[2][400005];  // previous occurrence positions
int cnt(int c, int l, int r) { return pres[c][r] - pres[c][l - 1]; }
struct segtree {
  int k;
  int mx[1111111];
  int l[1111111], r[1111111];
  void Build(int n) {
    k = 1;
    while (k < n)
      k *= 2;
    for (int i = 0; i < k; i++)
      l[i + k] = i, r[i + k] = i;
    for (int i = k - 1; i >= 1; i--)
      l[i] = l[2 * i], r[i] = r[2 * i + 1];
    for (int i = 1; i < 2 * k; i++)
      mx[i] = -mod;
  }
  int Max(int p, int ll, int rr) {
    if (ll > r[p] || rr < l[p])
      return -mod;
    if (ll <= l[p] && rr >= r[p])
      return mx[p];
    return max(Max(2 * p, ll, rr), Max(2 * p + 1, ll, rr));
  }
  void Upd(int i, int x) {
    i += k, mx[i] = x, i >>= 1;
    while (i) {
      mx[i] = max(mx[2 * i], mx[2 * i + 1]);
      i >>= 1;
    }
  }
  void ispisi() {
    for (int kk = 1; kk <= k; kk *= 2) {
      for (int i = kk; i < 2 * kk; i++) {
        if (mx[i] < 0)
          cout << "x" << " ";
        else
          cout << mx[i] << " ";
      }
      cout << endl;
    }
  }
} MST[2];
int dp[400005]; // dynamic programming array
int l[400005], r[400005], bc[400005]; // block information
int nj[400005]; // helper array for binary search
int ni[400005]; // helper array for binary search
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int tests;
  cin >> tests;
  while (tests--) {
    string s;
    cin >> s;
    string t;
    cin >> t;
    int n = (int)s.size();
    for (int i = 0; i <= n + 1; i++)
      pres[0][i] = 0, pres[1][i] = 0, pret[0][i] = 0, pret[1][i] = 0, ni[i] = 0,
      nj[i] = 0, l[i] = 0, r[i] = 0, bc[i] = 0, dp[i] = 0;
    s = "x" + s, t = "x" + t;
    // Precompute prefix sums for character counts
    for (int i = 1; i <= n; i++) {
      for (int c = 0; c <= 1; c++) {
        pres[c][i] = pres[c][i - 1] + (s[i] == '0' + c);
        pret[c][i] = pret[c][i - 1] + (t[i] == '0' + c);
      }
    }
    // Compute next occurrence of characters
    for (int c = 0; c <= 1; c++)
      nxt[c][n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
      for (int c = 0; c <= 1; c++) {
        nxt[c][i] = nxt[c][i + 1];
        if (t[i] == '0' + c)
          nxt[c][i] = i;
      }
    }
    // Compute previous occurrence of characters
    for (int c = 0; c <= 1; c++)
      prv[c][0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int c = 0; c <= 1; c++) {
        prv[c][i] = prv[c][i - 1];
        if (t[i] == '0' + c)
          prv[c][i] = i;
      }
    }
    // Identify blocks in string s
    int m = 1;
    l[m] = 1, r[m] = 1, bc[m] = (s[1] - '0');
    for (int i = 2; i <= n; i++) {
      if (s[i] == s[i - 1])
        r[m]++;
      else {
        ++m;
        l[m] = i, r[m] = i, bc[m] = (s[i] - '0');
      }
    }
    l[m + 1] = n + 1, r[m + 1] = n + 1, bc[m + 1] = !bc[m];
    // Initialize dp array
    for (int i = 0; i <= m + 1; i++)
      dp[i] = -mod;
    dp[0] = 0;
    // Binary search to find optimal block placements
    for (int i = 1; i <= m + 1; i++) {
      int c = !bc[i];
      int p = -1, q = i;
      while (q - p > 1) {
        int j = p + (q - p) / 2;
        if (cnt(c, l[j + 1], r[i - 1]) >= prv[c][r[i - 1]] - r[j])
          q = j;
        else
          p = j;
      }
      nj[i] = q;
    }
    // Prepare for segment tree updates
    vector<vector<int>> dekonsideruj[2];
    for (int c = 0; c <= 1; c++)
      dekonsideruj[c].resize(m + 3);
    for (int j = 0; j <= m; j++) {
      int c = !bc[j + 1];
      int p = j, q = m + 2;
      while (q - p > 1) {
        int i = p + (q - p) / 2;
        if (cnt(!c, l[j + 1], r[i - 1]) >= l[i] - nxt[!c][l[j + 1]])
          p = i;
        else
          q = i;
      }
      ni[j] = p;
      dekonsideruj[c][ni[j] + 1].push_back(j);
    }
    // Build segment trees
    for (int c = 0; c <= 1; c++)
      MST[c].Build(m + 2);
    MST[!bc[1]].Upd(0, dp[0]);
    // Dynamic programming
    for (int i = 1; i <= m + 1; i++) {
      for (int c = 0; c <= 1; c++) {
        for (auto it : dekonsideruj[c][i]) {
          MST[c].Upd(it, -mod);
        }
      }
      int c = !bc[i];
      if (i <= m && pret[c][r[i]] - pret[c][l[i] - 1] > 0)
        continue;
      dp[i] = MST[c].Max(1, nj[i], i - 1) + 1;
      MST[!c].Upd(i, dp[i]);
    }
    // Output result
    if (dp[m + 1] < 0)
      cout << -1 << "\n";
    else
      cout << (m + 1 - dp[m + 1]) / 2 << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/