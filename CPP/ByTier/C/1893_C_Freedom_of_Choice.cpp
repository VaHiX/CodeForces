// Problem: CF 1893 C - Freedom of Choice
// https://codeforces.com/contest/1893/problem/C

/*
Algorithm: Greedy with Binary Search and Counter Manipulation
Approach:
- For each multiset, we determine how many copies of each number we can use to minimize anti-beauty.
- We calculate the minimum number of occurrences of the size of the resulting multiset (anti-beauty).
- The key idea is to process each number (from L to R) and compute how many times it can be used in the final multiset.

Time Complexity: O(sum of n_i) where sum of n_i <= 10^5
Space Complexity: O(R - L) which is at most 10^5 in the worst case.

The approach essentially simulates choosing elements greedily such that the count of the final multiset size is minimized.
*/

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define endl '\n'
using namespace std;
typedef long long ll;
const ll N = 2e5 + 10, LOG = 20, mod = 1e9 + 7;
void solve() {
  ll m;
  cin >> m;
  vector<ll> ni(m), l(m), r(m), t(m);
  vector<ll> a[m], c[m];
  ll L = 0, R = 0, N = 0;
  for (ll i = 0; i < m; i++) {
    cin >> ni[i] >> l[i] >> r[i];
    a[i].resize(ni[i]);
    c[i].resize(ni[i]);
    for (ll j = 0; j < ni[i]; j++) {
      cin >> a[i][j];
    }
    for (ll j = 0; j < ni[i]; j++) {
      cin >> c[i][j];
      t[i] += c[i][j];
    }
    L += l[i];
    R += r[i];
    N += ni[i];
  }
  // If total elements we can select exceeds total distinct numbers, we can reduce anti-beauty to 0
  if (R - L > N) {
    cout << "0" << endl;
    return;
  }
  // cnt[i] = max number of copies of element (L+i) we can have in final multiset
  // left[i] = number of elements in [L, R] with less than l[i] copies in final multiset
  vector<ll> cnt(R - L + 1, R), left(R - L + 1, 0);
  for (ll i = 0; i < m; i++) {
    for (ll j = 0; j < ni[i]; j++) {
      if (a[i][j] >= L && a[i][j] <= R) {
        ll num = t[i] - c[i][j];
        if (num >= l[i]) {
          // If even the minimum required copies are satisfied
          cnt[a[i][j] - L] -= max(r[i] - num, 0LL);
        } else {
          // If not all copies are used, we may need some to satisfy l[i]
          cnt[a[i][j] - L] -= r[i] - num;
          left[a[i][j] - L] += l[i] - num;
        }
      }
    }
  }
  ll ans = INT64_MAX;
  // For each possible target size, calculate the maximum number of times it can occur
  for (ll i = L; i <= R; i++) {
    ans = min(ans, max(i - cnt[i - L], left[i - L]));
  }
  cout << ans << endl;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  ll t = 1;
  cin >> t;
  for (ll i = 1; i <= t; i++) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/