// Problem: CF 1951 D - Buying Jewels
// https://codeforces.com/contest/1951/problem/D

/*
Algorithm/Techniques: Greedy approach with mathematical analysis
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves determining whether it's possible to set up at most 60 stalls 
such that Alice buys exactly k jewels, given n coins and greedy purchasing behavior.

Key insight:
- If k == n, we can use one stall with price 1, buying all jewels.
- If k is small enough (k <= n - n/2 + 1), we can strategically place two stalls:
  - First stall buys (n - (k - 1)) jewels, leaving (k - 1) coins.
  - Second stall buys 1 jewel per coin, so we just need k jewels in total.
- Otherwise, it's impossible within the limit of 60 stalls due to constraints.
*/

#include <stdint.h>
#include <iostream>

using namespace std;

void solve() {
  int64_t n, k;
  cin >> n >> k;
  int64_t value = n / 2 + 1; // This represents a threshold to determine if k is small enough

  if (n == k) {
    // When n equals k, we can buy all jewels at price 1 per jewel
    cout << "YES" << '\n';
    cout << "1" << '\n';
    cout << "1" << '\n';
  } else if (k <= n - value + 1) { // Check if k is small enough to fit in two stalls
    cout << "YES" << '\n';
    if (k == 1) {
      // Special case: only one jewel to buy, so put all coins in one stall
      cout << "1" << '\n';
      cout << n << '\n';
    } else {
      // General case with two stalls
      cout << "2" << '\n';
      cout << n - (k - 1) << " 1" << '\n'; // price of first stall, then 1 for second
    }
  } else {
    // If k is too large to satisfy with at most two stalls, it's impossible
    cout << "NO" << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/