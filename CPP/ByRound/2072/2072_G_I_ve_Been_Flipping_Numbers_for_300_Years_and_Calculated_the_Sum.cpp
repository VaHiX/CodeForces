// Problem: CF 2072 G - I've Been Flipping Numbers for 300 Years and Calculated the Sum
// https://codeforces.com/contest/2072/problem/G

/*
G. I've Been Flipping Numbers for 300 Years and Calculated the Sum
Problem Description:
Given a number n and an upper limit k, compute the sum of rev(n, p) for all bases p from 2 to k.
rev(n, p) is defined as reversing the base-p representation of n and converting it back to decimal.

Algorithms/Techniques:
- Mathematical optimization using block processing for large ranges of bases
- Digit sum calculations in different bases
- Efficient modular arithmetic

Time Complexity: O(k^(2/3) + T * sqrt(k)) where T is number of test cases
Space Complexity: O(1)

*/

#include <iostream>

#define ll long long
using namespace std;
const int P = 1e9 + 7;
ll n, k, ans;

// Calculate sum of arithmetic sequence from l to r
ll sum(ll l, ll r) { return (r + l) * (r - l + 1) / 2; }

// Calculate sum of squares from 1 to x
ll sum2(ll x) { return x * (x + 1) * (x + x + 1) / 6; }

void solve() {
  cin >> n >> k;
  if (n == 1) {
    cout << (k - 1) % P << endl;
    return;
  }
  if (k > n) {
    // If k exceeds n, add contribution of all bases from n+1 to k
    ans = (k - n) % P * n % P;
    k = n;
  } else {
    ans = 0;
  }

  // Main loop for processing blocks of bases efficiently
  for (ll r = k, l;; r = l - 1) {
    ll t = n / r; // quotient when dividing n by r
    l = n / (t + 1) + 1; // calculate left bound for current block

    if (t >= l) { // this condition marks the end of block processing
      k = r;
      break;
    }
    // Compute contribution of current block
    ans =
        (ans + n * sum(l, r) - t * (sum2(r) - sum2(l - 1)) + t * (r - l + 1)) %
        P;
  }

  // Process remaining bases from k down to 2 directly
  for (ll r = k; r >= 2; r--) {
    ll x = n, sum = 0;
    while (x) {
      sum *= r;
      sum += x % r;
      x /= r;
    }
    ans += sum;
    ans -= ans < P ? 0 : P; // Handle modulo correctly
  }

  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/