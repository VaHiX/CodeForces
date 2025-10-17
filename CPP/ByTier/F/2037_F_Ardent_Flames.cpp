// Problem: CF 2037 F - Ardent Flames
// https://codeforces.com/contest/2037/problem/F

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

#define endl '\n'
#define ll long long
#define pb push_back
#define mp make_pair
using namespace std;
const int MAXN = 1e5 + 100;
typedef pair<int, int> pii;
int t, n, m, k;
int x[MAXN], h[MAXN];
vector<pii> vc;

/**
 * @brief Checks if it's possible to defeat at least k enemies with at most 'md' damage per attack.
 * 
 * Uses a sweep line technique:
 * - For each enemy, calculate the range where it can be damaged by 'md'.
 * - Create events (start/end) of intervals and sweep through them.
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */
bool chk(int md) {
  vc.clear();
  for (int i = 0; i < n; i++) {
    int d = (h[i] + md - 1) / md; // rounds up the number of hits needed to defeat enemy
    int rng = m - d;             // range over which damage is applied
    if (rng < 0)
      continue;
    vc.pb(mp(max(1, x[i] - rng), 1));                 // start of interval
    vc.pb(mp(min(x[i] + rng, (int)(1e9)) + 1, -1));   // end of interval
  }
  sort(vc.begin(), vc.end());                        // sweep line: sort intervals by position
  int cnt = 0;
  for (auto [wtf, x] : vc) {                         // iterate through events
    cnt += x;                                        // add or remove from active count
    if (cnt >= k)
      return 1;                                      // can defeat enough enemies
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
      cin >> h[i];
    for (int i = 0; i < n; i++)
      cin >> x[i];
    ll l = 0, r = 1e9, md;
    while (r - l > 1) {
      md = (l + r) >> 1;     // binary search on damage value
      if (chk(md))
        r = md;
      else
        l = md;
    }
    if (!chk(r))
      cout << -1 << endl;
    else
      cout << r << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/