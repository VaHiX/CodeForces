// Problem: CF 1777 F - Comfortably Numb
// https://codeforces.com/contest/1777/problem/F

/*
 * Problem: F. Comfortably Numb
 * Algorithm: Optimized Segment Tree with DSU on Tree + Trie
 * Description:
 *   Given an array of non-negative integers, find the maximum "numbness" 
 *   over all subarrays, where numbness of subarray [l, r] is defined as:
 *   max(a_l, ..., a_r) XOR (a_l XOR ... XOR a_r).
 *   
 * Approach:
 *   - Use a Cartesian tree to decompose the problem into segments.
 *   - Apply DSU on Tree technique to efficiently traverse and query.
 *   - Maintain a trie to quickly find maximum XOR value for a given prefix.
 *   
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define ff first
#define ss second
#define pb push_back
#define llf __ll128
#define ll long long
#define ld long double
#define pii pair<ll, ll>
#define pli pair<ll, ll>
#define pll pair<ll, ll>
#define DECIMAL_OUTPUT cout << fixed << setprecision(9);
#define RUN_LIKE_DJAWAD                                                        \
  (ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr));
#pragma GCC optimize("Ofast")
const int maxn = 2e5 + 1;
const int lg = 3e1;
const int maxnd = 6e6 + 1;
int ch[maxnd][2]; // Trie structure for storing XOR values
int ct[maxn][2];  // Cartesian tree structure
int cn, atx, n;   // cn: node counter, atx: accumulated XOR
int na[maxn];     // input array
int pp2[lg];      // Powers of 2 for bit manipulation

// Add a number to the trie
void add(int x) {
  int node = 0;
  for (int i = lg - 1; i >= 0; i--) {
    bool bit = x & pp2[i];
    if (ch[node][bit] == 0)
      ch[node][bit] = ++cn;
    node = ch[node][bit];
  }
}

// Get maximum XOR with a given value using trie
int get_max(int x) {
  int node = 0, ans = 0;
  x ^= atx; // Adjust for current prefix
  for (int i = lg - 1; i >= 0; i--) {
    bool bit = x & pp2[i];
    if (ch[node][bit ^ 1] != 0) {
      ans += pp2[i];
      node = ch[node][bit ^ 1];
    } else
      node = ch[node][bit];
  }
  return ans;
}

// Reset trie to initial state
void RESET_TRIE() {
  for (int i = 0; i <= cn; i++)
    ch[i][0] = 0, ch[i][1] = 0;
  cn = 0;
  atx = 0;
}

// Reset Cartesian tree
void RESET_TREAP() {
  for (int i = 0; i <= n; i++)
    ct[i][0] = 0, ct[i][1] = 0;
}

// Read input for current test case
void INPUT() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> na[i];
}

int ml[maxn], mr[maxn]; // Left and right boundaries in Cartesian tree
int rl[maxn], rr[maxn]; // Range for DFS traversal in Cartesian tree

// Build Cartesian tree
void BUILD_CARTESIAN_TREE() {
  vector<int> stk = {0};
  for (int i = 1; i <= n; i++)
    ml[i] = -1, mr[i] = -1;
  na[0] = 1e9 + 1;
  for (int i = 1; i <= n; i++) {
    while (na[stk.back()] < na[i]) {
      mr[stk.back()] = i;
      stk.pop_back();
    }
    ml[i] = stk.back();
    stk.pb(i);
  }
  for (int i = 1; i <= n; i++) {
    if (ml[i] == -1) {
      ct[mr[i]][0] = i;
    } else if (mr[i] == -1) {
      ct[ml[i]][1] = i;
    } else {
      if (na[ml[i]] < na[mr[i]])
        ct[ml[i]][1] = i;
      else
        ct[mr[i]][0] = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (mr[i] == -1)
      rr[i] = n;
    else
      rr[i] = mr[i] - 1;
    rl[i] = ml[i] + 1;
  }
}

int pref[maxn]; // Prefix XOR array

// Build prefix XOR array
void BUILD_XOR_PREFIX() {
  pref[0] = 0;
  for (int i = 1; i <= n; i++)
    pref[i] = pref[i - 1] ^ na[i];
}

// Precompute powers of 2
void BUILD_PP2() {
  pp2[0] = 1;
  for (int i = 1; i < lg; i++)
    pp2[i] = pp2[i - 1] << 1;
}

// Compute XOR of subarray [l, r]
int xo(int l, int r) { return pref[r] ^ pref[l - 1]; }

int ans = 0; // Final answer

// Merge and compute results during DSU traversal
void DSU_MERGE(int l, int mx, int r, bool nm) {
  if (mx - l >= r - mx) {
    for (int i = mx; i <= r; i++)
      ans = max(ans, get_max(pref[i] ^ pref[l - 1] ^ na[mx]));
    if (nm)
      for (int i = mx; i <= r; i++)
        add(pref[i] ^ pref[l - 1] ^ atx);
  } else {
    for (int i = l; i <= mx; i++)
      ans = max(ans, get_max(pref[mx] ^ pref[i - 1] ^ na[mx]));
    atx ^= pref[mx] ^ pref[l - 1];
    if (nm)
      for (int i = l; i <= mx; i++)
        add(pref[i - 1] ^ pref[l - 1] ^ atx);
  }
}

// DFS traversal on DSU tree with trie updates
void dfs(int v, bool keep) {
  if (ct[v][0] == 0 and ct[v][1] == 0) {
    if (keep) {
      add(atx);
      add(na[v] ^ atx);
    }
    return;
  }
  if (ct[v][0] == 0)
    dfs(ct[v][1], true);
  else if (ct[v][1] == 0)
    dfs(ct[v][0], true);
  else {
    if (v - rl[v] >= rr[v] - v) {
      dfs(ct[v][1], false);
      dfs(ct[v][0], true);
    } else {
      dfs(ct[v][0], false);
      dfs(ct[v][1], true);
    }
  }
  DSU_MERGE(rl[v], v, rr[v], keep);
  if (not keep)
    RESET_TRIE();
}

// Solve a single test case
void solved() {
  RESET_TRIE();
  RESET_TREAP();
  INPUT();
  BUILD_CARTESIAN_TREE();
  BUILD_PP2();
  BUILD_XOR_PREFIX();
  ans = 0;
  dfs(ct[0][1], false);
  cout << ans << "\n";
}

int t;
int main() {
  RUN_LIKE_DJAWAD
  cin >> t;
  while (t--)
    solved();
}


// https://github.com/VaHiX/CodeForces/