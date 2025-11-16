// Problem: CF 806 A - Success Rate
// https://codeforces.com/contest/806/problem/A

/*
Purpose: This program determines the minimum number of additional submissions needed to achieve a desired success rate p/q, given current x successful submissions out of y total submissions.

Algorithm:
- Binary search on the number of total submissions (t) to find the smallest t such that:
    1. p * t >= x (ensuring enough successful submissions)
    2. q * t - p * t >= y - x (ensuring enough unsuccessful submissions)
- Time Complexity: O(log(10^9)) per test case due to binary search.
- Space Complexity: O(1), only using a few variables.

Techniques:
- Binary search on answer
- Mathematical constraints check for valid submission counts
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
typedef long long ll;

// Check if with 't' total submissions, we can achieve success rate p/q
bool check(ll x, ll y, ll p, ll q, ll t) {
  return p * t >= x && q * t - p * t >= y - x;
}

void solve() {
  ll x, y, p, q;
  scanf("%lld%lld%lld%lld", &x, &y, &p, &q);
  
  ll l = -1;
  ll r = (ll)1e9;
  
  // If even maximum allowed submissions can't satisfy the condition, return -1
  if (!check(x, y, p, q, r)) {
    printf("-1\n");
    return;
  }
  
  // Binary search for the minimum valid total submissions
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (check(x, y, p, q, m)) {
      r = m; // Try to minimize number of submissions
    } else {
      l = m; // Need more submissions
    }
  }
  
  // The result is how many new submissions are needed
  printf("%lld\n", r * q - y);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/