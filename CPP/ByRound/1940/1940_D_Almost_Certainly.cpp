// Problem: CF 1940 D - Almost Certainly
// https://codeforces.com/contest/1940/problem/D

#include <algorithm>
#include <iostream>
#include <set>
#include <utility>

#define fi first
#define se second
#define ll long long
#define pii pair<ll, ll>
using namespace std;
const ll INF = 1e18;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll a[n + 1];
    ll b[n + 1];
    set<pii> st; // Set to maintain intervals of (b[i], a[i]) in sorted order
    ll mx = 0; // Maximum difference a[i] - b[i] seen so far
    for (ll i = 1; i <= n; ++i)
      cin >> a[i];
    for (ll i = 1; i <= n; ++i)
      cin >> b[i];
    ll sum = 0; // Cumulative sum of differences a[i] - b[i]
    for (ll i = 1; i <= n; ++i) {
      sum += a[i] - b[i]; // Add current difference to cumulative sum
      if (st.empty()) {
        // If the set is empty, insert the first interval
        st.insert({b[i], a[i]});
        mx = max(mx, a[i] - b[i]); // Update maximum difference
      } else {
        // Find upper bound in the set for (b[i], INF)
        auto rg = st.upper_bound({b[i], INF});
        auto lf = rg;
        lf--; // Reference to the element before upper bound
        
        // If the current interval fits inside an existing interval
        if (rg != st.begin() && (*lf).fi <= b[i] && a[i] <= (*lf).se) {
          cout << sum - mx << ' '; // Output the minimum operations needed
          continue;
        }
        // Adjust b[i] if it overlaps with the previous interval
        if (rg != st.begin() && b[i] <= (*lf).se) {
          b[i] = (*lf).fi;
          st.erase(lf);
        }
        // Merge with subsequent intervals as long as they overlap
        while (rg != st.end() && (*rg).fi <= a[i]) {
          a[i] = max(a[i], (*rg).se);
          st.erase(rg);
          rg = st.upper_bound({b[i], INF});
        }
        st.insert({b[i], a[i]}); // Insert the updated interval
        mx = max(mx, a[i] - b[i]); // Update max difference
      }
      cout << sum - mx << ' '; // Output result for current prefix
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/