// Problem: CF 1846 E2 - Rudolf and Snowflakes (hard version)
// https://codeforces.com/contest/1846/problem/E2

/*
E2. Rudolf and Snowflakes (hard version)
Algorithm: Check if a number n can be represented as a geometric series sum:
n = 1 + k + k^2 + ... + k^(i-1) for some integer k > 1 and i >= 2.
This represents the total number of vertices in a snowflake with parameter k and depth i.

Time Complexity: O(log(n) * log(log(n))) per test case, due to iterating over possible exponents up to ~60,
and for each exponent checking if the geometric sum equals n.

Space Complexity: O(1), only using constant extra space.
*/

#include <cmath>
#include <iostream>
#define int long long
#define endl "\n"
using namespace std;
int n, m, k, t;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    int x = 0;
    int f = 0;
    for (int i = 2; i <= 60; i++) {  // Loop through possible depths i (from 2 to 60)
      k = pow(n, 1.0 / i);           // Estimate k as the i-th root of n
      m = 1 + k;                     // Initialize sum with 1 + k
      x = k * k;                     // Set x to k^2 for geometric progression
      if (k < 2)                     // Skip if k is less than 2
        continue;
      for (int j = 2; j <= i; j++) { // Compute sum: 1 + k + k^2 + ... + k^(i-1)
        m += x;                      // Add current power of k
        x *= k;                      // Move to next power
      }
      if (m == n) {                  // If computed sum matches n
        f = 1;                       // Mark as found
        break;
      }
    }
    if (f) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/