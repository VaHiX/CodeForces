// Problem: CF 1899 F - Alex's whims
// https://codeforces.com/contest/1899/problem/F

/*
Code Purpose:
This code solves the problem of constructing a tree and performing operations to ensure that for each day, 
there exist two leaves in the tree at a specific distance d_i. The approach uses a linear tree structure 
and strategically performs edge reconfiguration operations to adjust distances between leaves.

Algorithms/Techniques:
- Linear tree construction: Build a path of n nodes (1-2-3-...-n)
- Operation strategy: When a required distance is not available, 
  rewire edges from the last node to maintain control over leaf distances
- Greedy approach for operation selection

Time Complexity: O(n + q)
Space Complexity: O(q) for storing distances

*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <functional>
#include <iostream>

using namespace std;
using namespace __gnu_pbds;
#define clr(x) vector<int>().swap(x);
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define lb lower_bound
#define ub upper_bound
#define endl '\n'
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vvi vector<vector<int>>
#define vii vector<pii>
#define random                                                                 \
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());      \
  mt19937 rnd(time(0));
#define FAST                                                                   \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define F first
#define S second
#define le v * 2
#define re v * 2 + 1
#define tm (tl + tr) / 2
const ll INF = 9e18;
const ll MN = -2e9;
const ll MX = 5e2 + 9;
const ll MXX = 2e9;
const ll SQ = 5e2;
const ll MOD = 1e9 + 7;
const ll PP = 1e6 + 3;
const ld PI = 3.141592653589793;
const ld eps = 1e-9;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
int n, m, p, q, d, a[MX];
void solve() {
  cin >> n >> m; // Read number of vertices and days
  for (int i = 0; i < m; i++)
    cin >> a[i]; // Read required distances for each day
  
  // Build a linear tree: 1-2-3-...-n
  for (int i = 1; i < n; i++)
    cout << i << " " << i + 1 << endl;
    
  // Initialize pointer to the last node
  p = d = n - 1;
  
  // Process each day
  for (int i = 0; i < m; i++) {
    if (a[i] == d)
      // If required distance matches current maximum, no operation needed
      cout << "-1 -1 -1" << endl;
    else {
      // Perform operation to adjust the tree to achieve required distance
      q = d = a[i]; // Update target distance
      cout << n << " " << p << " " << q << endl; // Operation: move edge from p to q
      p = q; // Update pointer
    }
  }
}
int main() {
  FAST;
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/