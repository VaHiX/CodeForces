// Problem: CF 2043 D - Problem about GCD
// https://codeforces.com/contest/2043/problem/D

/*
D. Problem about GCD
time limit per test1 second
memory limit per test256 megabytes

Given three integers l, r, and G, find two integers A and B (l <= A <= B <= r) such that their greatest common divisor (GCD) equals G and the distance |A−B| is maximized.
If there are multiple such pairs, choose the one where A is minimized. If no such pairs exist, output "-1 -1".

Algorithm:
- First, we transform the problem by dividing l, r, and G by G to reduce it to finding coprime numbers in a range.
- Then we iterate from the maximum possible difference down to 0.
- For each difference i, check if there exists a pair (x, x + i) such that gcd(x, x + i) == 1.
- Since gcd(x, x + i) = gcd(x, i), we only need to check if gcd(i, x) = 1.
- We iterate through valid values of x and return the first valid pair found.

Time Complexity: O(√r * log(r)) per test case due to checking gcd for a few candidates in range.
Space Complexity: O(1)
*/

#include <iostream>
#include <numeric>

using namespace std;
using ll = long long;
ll l, r, G;

void solve() {
  cin >> l >> r >> G;
  // Transform the range to [lb, ub] where numbers are divisible by G
  ll lb = (l + G - 1) / G, ub = r / G;
  
  // Iterate from maximum possible difference down to 0
  for (ll i = ub - lb; i >= 0; --i) {
    // For each difference i, check all valid x values
    for (ll x = lb; x + i <= ub; ++x) {
      // Check if gcd(x, x+i) == 1: since gcd(x,x+i) = gcd(x,i), we simplify this
      if (gcd(x, x + i) == 1) {
        cout << x * G << ' ' << (x + i) * G << '\n';
        return;
      }
    }
  }
  cout << "-1 -1\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/