// Problem: CF 1876 C - Autosynthesis
// https://codeforces.com/contest/1876/problem/C

/*
Purpose: This code solves the "Autosynthesis" problem where we need to find a sequence of operations on an array such that the uncircled elements (in order) match the sequence of indices of elements that were circled. The solution uses graph theory and DFS to detect cycles and assign colors to nodes, which helps in determining if a valid sequence exists.

Algorithms/Techniques:
- Graph coloring using DFS
- Cycle detection in directed graphs
- Greedy assignment of operations

Time Complexity: O(n), where n is the size of the array. Each node is visited at most once.
Space Complexity: O(n), for storing the graph structure and auxiliary arrays.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
#define ii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vii vector<ii>
#define vll vector<ll>
#define vpll vector<pll>
#define msi multiset<int>
#define si set<int>
#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define MP make_pair
#define FOR(i, a, b) for (int i = int(a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
const int mod = 1e9 + 7;
const int MOD = 998244353;
const int inf = mod;
const ll INF = 1e18;
const int MAXN = 1e6 + 7;
const int logo = 20;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
int arr[MAXN], dg[MAXN], c[MAXN], uz[MAXN];
bool bio[MAXN];

// DFS function to color nodes and detect cycles
void dfs(int u, int col) {
  if (bio[u])
    return;
  c[u] = col;
  bio[u] = 1;
  uz[arr[u]] |= col;
  dg[arr[u]]--;
  if (dg[arr[u]] == 0)
    dfs(arr[u], col ^ 1); // Continue with alternating color
  else if (col == 1)
    dfs(arr[u], 0); // Continue with color 0 if col is 1
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    dg[arr[i]]++; // Count in-degrees
  }
  for (int i = 1; i <= n; i++)
    if (dg[i] == 0)
      dfs(i, 1); // Start DFS for nodes with in-degree 0

  for (int i = 1; i <= n; i++) {
    if (bio[i])
      continue;
    int cur = i, cl = 0;
    while (!bio[cur]) {
      bio[cur] = 1;
      c[cur] = cl; // Assign color
      uz[arr[cur]] |= cl; // Update used colors
      cur = arr[cur]; // Move to next node
      cl ^= 1; // Toggle color
    }
  }

  bool fl = 1;
  for (int i = 1; i <= n; i++) {
    if (c[i] and c[arr[i]]) // Check conflicting colors
      fl = 0;
    if (!c[i] and !uz[i]) // Check if color is valid
      fl = 0;
  }

  if (!fl)
    cout << -1 << "\n"; // Impossible to solve
  else {
    vi an;
    for (int i = 1; i <= n; i++)
      if (c[i])
        an.PB(arr[i]); // Collect operations
    cout << an.size() << "\n";
    for (auto &x : an)
      cout << x << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t = 1;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/