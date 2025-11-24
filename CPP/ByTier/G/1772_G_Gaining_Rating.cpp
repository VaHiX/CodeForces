// Problem: CF 1772 G - Gaining Rating
// https://codeforces.com/contest/1772/problem/G

/*
Algorithm: Greedy with Simulation
Time Complexity: O(n * log(n)) due to sorting and linear traversal
Space Complexity: O(n) for storing opponent ratings

The problem involves finding the minimum number of games to increase Monocarp's
rating from x to y. Monocarp can only play against opponents with rating <= his
current rating. Each win increases his rating by 1, each loss decreases it by 1.
The constraint is that he must play against all opponents as evenly as possible.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ld> vld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
#define pb push_back
#define mp make_pair
#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define fore(i, l, r) for (int i = int(l); i < int(r); ++i)
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  ll n, m, k, k1, k0, k2, l, r, x, y, t;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> l >> r;
    vll a(n);
    forn(i, n) cin >> a[i];
    std::sort(a.begin(), a.end());
    ll ls = l, p = -1;
    x = l;
    y = r;
    forn(i, n) {
      if (a[i] <= ls)
        ++ls; // If opponent's rating is <= current rating, win and increase
              // rating
      else {
        if (p == -1)
          p = i; // First opponent that cannot be beaten
        --ls;    // Otherwise, lose and decrease rating
      }
    }
    if (p + l >= y) {
      cout << y - x << '\n'; // If we can reach desired rating directly
      continue;
    }
    if (ls <= l) {
      cout << -1 << '\n'; // Impossible to increase rating further
      continue;
    }
    if (p == -1) {
      cout << y - x << '\n'; // All opponents can be beaten
      continue;
    }
    ll ans = 0;
    while (p < n) {
      // Calculate how many full rounds of playing all opponents are needed
      if (x + ((a[p] - (x + p) + ls - l - 1) / (ls - l)) * (ls - l) + p >= y) {
        ans += n * max(0ll, (y - x - p + ls - l - 1) / (ls - l)) + y -
               (x + (ls - l) * max(0ll, (y - x - p + ls - l - 1) / (ls - l)));
        p = n;
        break;
      }
      ans += n * ((a[p] - (x + p) + ls - l - 1) / (ls - l)); // Add full rounds
      x += ((a[p] - (x + p) + ls - l - 1) / (ls - l)) * (ls - l); // Update x
      while (p < n && x + p >= a[p]) {
        ++p;     // Move to next unbeat-able opponent
        ls += 2; // Increase ls to account for game rounds
      }
      if (p == n) {
        ans += y - x; // Final adjustment
      }
    }
    cout << ans << '\n';
  }
}

// https://github.com/VaHiX/CodeForces/