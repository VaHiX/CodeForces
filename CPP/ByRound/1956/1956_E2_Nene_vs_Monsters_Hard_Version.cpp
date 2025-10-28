// Problem: CF 1956 E2 - Nene vs. Monsters (Hard Version)
// https://codeforces.com/contest/1956/problem/E2

#pragma GCC optimize("O3")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
#define IOS                                                                    \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0)
#define ll long long
#define ld long double
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
const int MOD = 1e9 + 7;
const int MX = 2e5 + 5;
const ll INF = 1e18;
const ld PI = 4 * atan((ld)1);
const int xd[4] = {1, 0, -1, 0}, yd[4] = {0, 1, 0, -1};
const int L = 150;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int a[MX];
void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  // Apply the spell L times (150) to simulate the process
  for (int z = 0; z < L; ++z) {
    for (int i = 0; i < n - 1; ++i) {
      a[i + 1] -= a[i]; // Monster i attacks monster i+1
      if (a[i + 1] < 0) {
        a[i + 1] = 0; // Ensure energy doesn't go below 0
      }
    }
    a[0] -= a[n - 1]; // Last monster attacks first monster (circular)
    if (a[0] < 0) {
      a[0] = 0; // Ensure energy doesn't go below 0
    }
  }
  // Identify the pattern in the remaining energies after L iterations
  int st[3];
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0) {
      st[0] = (i + 1) % n; // Find first non-zero index
    } else {
      // This logic appears to compute a difference, but is unclear
      a[i + 1] = max(0, a[i + 1] - a[i]);
    }
  }
  st[1] = (st[0] + 1) % n; // Next index in circle
  st[2] = (st[0] + 2) % n; // Next to next index in circle

  vector<int> res;
  // Check potential survivors using circular sliding window
  for (int i = 0; i < n; ++i) {
    if (a[st[0]] != 0) { // If the monster at st[0] still has energy
      res.push_back(st[0]); // Add this monster's index to result
      if (a[st[2]] == 0) { // If next to next monster has no energy
        a[st[1]] = 0; // Then monster at st[1] also gets zero
      } else {
        // Complex computation to determine if monster st[1] survives
        int cnt = a[st[1]] / a[st[0]]; // Compute how many times st[0] can attack st[1]
        if (1ll * (a[st[1]] - a[st[0]] + a[st[1]] % a[st[0]]) * cnt / 2 >=
            a[st[2]]) { // Complex condition to detect pattern
          a[st[1]] = a[st[2]] = 0; // Mark both as dead
        } else {
          a[st[1]] = 0; // Otherwise, only st[1] dies
        }
      }
    }
    st[0] = st[1];         // Slide window
    st[1] = st[2];         // Slide window
    st[2] = (st[2] + 1) % n; // Slide window
  }
  cout << res.size() << '\n';
  sort(res.begin(), res.end());
  for (auto x : res) {
    cout << x + 1 << ' '; // Output indices in 1-based
  }
  cout << '\n';
}
int main() {
  IOS;
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/