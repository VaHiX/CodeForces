// Problem: CF 2124 E - Make it Zero
// https://codeforces.com/contest/2124/problem/E

/*
E. Make it Zero
Algorithms/Techniques: Prefix sums, greedy assignment, constructive algorithm.
Time Complexity: O(n) per test case.
Space Complexity: O(n) for storing the array and prefix sums.

Given an array of positive integers, we want to reduce all elements to zero using minimal operations.
Each operation allows choosing a vector b such that the sum of first i elements equals sum of last n-i elements,
and then subtract b[i] from a[i].

Approach:
- First check for trivial case: if total sum is even and there exists a prefix with sum = total/2, one operation suffices.
- Otherwise, try to find how we can split the array so that after removing one element (at index P), 
  the remaining array can be divided into two parts with equal sum through a greedy assignment strategy.
*/

#include <algorithm>
#include <array>
#include <iostream>

using namespace std;
using ll = long long;
const ll N = 5e4 + 5;
ll a[N], p[N], n;

void aua() {
  for (int i = 1; i <= n; ++i)
    cout << a[i] << ' ';
  cout << '\n';
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    cin >> a[i];
  for (int i = 1; i <= n; ++i)
    p[i] = p[i - 1] + a[i];

  // Check if we can split once
  for (int i = 1; i < n; ++i) {
    if (p[i] == p[n] - p[i]) {
      cout << 1 << '\n';
      aua();
      return;
    }
  }

  ll P = 0;
  // Find the first index where prefix sum >= total/2
  for (int i = 1; i <= n; ++i)
    if (p[i - 1] < p[n] / 2 && p[i] >= p[n] / 2)
      P = i;

  // Impossible cases:
  // No such splitting point found.
  // Or total sum is odd.
  // Or max element > half of total sum.
  if (!P || p[n] & 1 || *max_element(a + 1, a + n + 1) > p[n] / 2) {
    cout << -1 << '\n';
    return;
  }

  cout << 2 << '\n';

  // Create del array to store three parts:
  // del[0]: sum of first P-1 elements,
  // del[1]: sum needed from element P to balance suffix,
  // del[2]: remaining part to be balanced.

  array<ll, 3> del = {p[P - 1], p[P - 1] - (p[n] - 2 * a[P]) / 2,
                      p[P - 1] - del[1]};

  for (int i = 1; i <= n; ++i) {
    // Determine which part the current element belongs to
    ll t = (i < P ? 0 : i == P ? 1 : 2);
    // Take minimum of what is needed or available in a[i]
    ll x = min(a[i], del[t]);
    cout << x << ' ';
    // Update remaining amounts
    del[t] -= x;
    a[i] -= x;
  }
  cout << '\n';
  aua();
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/