// Problem: CF 2055 E - Haystacks
// https://codeforces.com/contest/2055/problem/E

/*
E. Haystacks

Problem Description:
We are given n haystacks, each with an initial number of haybales (a[i]) and a height limit after it's emptied for the first time (b[i]). 
Our goal is to find the minimum number of moves required so that every haystack has been emptied at least once. 
Once a haystack is emptied, it cannot accept more than b[i] haybales.

Algorithm:
- Sort haystacks based on specific criteria to optimize the order of emptying.
- Use prefix and suffix maximums to determine optimal trade-offs when moving haybales.
- Determine the minimum moves required to make all haystacks empty.

Time Complexity: O(n log n) due to sorting, where n is number of haystacks.
Space Complexity: O(n) for storing arrays and data structures.

Approach:
1. Sort haystacks with a custom comparator that prioritizes those which are more "beneficial" to be emptied first.
2. Precompute prefix maximums (pm) and suffix maximums (sm) for efficient calculation.
3. For each potential first emptying candidate, calculate the cost of moving haybales to achieve full emptiness.
4. Return minimum moves or -1 if impossible.

*/

#include <algorithm>
#include <iostream>

#pragma GCC optimize("Ofast")
using namespace std;
#define endl '\n'
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3f
#define MOD 1000000007
typedef long long ll;
const int N = 5e5 + 2;

struct ab {
  int a, b;
  bool operator<(const ab &o) const {
    // Custom sort criteria:
    // Count how many conditions (b > a) and (b >= a) hold for current and other
    int x = (b > a) + (b >= a);
    int y = (o.b > o.a) + (o.b >= o.a);
    if (x != y)
      return x > y; // Prefer the one with more conditions met
    if (x == 2)
      return a < o.a; // If both have same count, prefer smaller a
    return b > o.b;   // If both have only 1 condition met, prefer larger b
  }
};

int t, n;
ab p[N];
ll a[N], b[N], pm[N], sm[N]; // a and b are prefix sums of a[i], b[i]
ll oa[N], ob[N]; // For unused storage (possibly old variable names)

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> p[i].a >> p[i].b;
    }
    sort(p + 1, p + 1 + n); // Sort using custom comparator
    for (int i = 1; i <= n; i++) {
      a[i] = a[i - 1] + p[i].a; // Prefix sum of haybales
      b[i] = b[i - 1] + p[i].b; // Prefix sum of limits
    }
    // Compute prefix maximum of (a[i] - b[i-1]) for optimization
    for (int i = 1; i <= n; i++) {
      pm[i] = max(pm[i - 1], a[i] - b[i - 1]);
    }
    sm[n] = 0;
    // Compute suffix maximum of (-a[n] + a[i] + b[n-1] - b[i-1]) for optimization
    for (int i = n - 1; i >= 1; i--) {
      ll as = a[n] - a[i];       // Sum from i+1 to n
      ll bs = b[n - 1] - b[i - 1]; // Sum from i to n-1 of limits
      sm[i] = max(sm[i + 1], -as + bs);
    }
    ll ans = INFL;
    for (int i = 1; i <= n; i++) {
      if (a[n] <= b[n] - p[i].b) { // Check if we can empty i'th haystack
        ll cur = pm[i - 1];       // Take prefix value until before i
        if (i != n) {
          // Add suffix optimization if not at last one
          cur = max(cur, sm[i + 1] + (a[n] - p[i].a) - (b[n - 1] - p[i].b));
        }
        ans = min(ans, cur); // Update minimum moves needed
      }
    }
    if (ans == INFL)
      cout << -1 << endl;       // Impossible case
    else
      cout << ans + a[n] << endl; // Final answer adjusted with total sum
  }
}


// https://github.com/VaHiX/codeForces/