// Problem: CF 1744 E2 - Divisible Numbers (hard version)
// https://codeforces.com/contest/1744/problem/E2

/*
Algorithm: 
The problem asks to find two numbers x and y such that:
1. a < x <= c
2. b < y <= d
3. x * y is divisible by a * b

Approach:
1. Find all divisors of a and b.
2. For each pair of divisors (i, j) where i divides a and j divides b:
   - Compute k = i * j.
   - Try to find the smallest multiple of k that is greater than a (r1).
   - Compute the corresponding y value such that (a * b) / k divides (x * y), which means y must be a multiple of (a * b) / k.
   - Check if both x and y satisfy the constraints.

Time Complexity: O(sqrt(a) + sqrt(b) + sqrt(a) * sqrt(b) * log(c) * log(d)) 
Space Complexity: O(sqrt(a) + sqrt(b))

Note: The search is optimized with early breaks and logarithmic operations for finding multiples.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
ll i, j, k, n, m, t, a, b, c, d, r1, r2;
int main() {
  cin >> t;
  while (t--) {
    cin >> a >> b >> c >> d;
    vector<ll> v1, v2;
    // Find all divisors of a
    for (i = 1; i * i <= a; i++) {
      if (!(a % i)) {
        v1.push_back(i);
        v1.push_back(a / i);
      }
    }
    // Find all divisors of b
    for (i = 1; i * i <= b; i++) {
      if (!(b % i)) {
        v2.push_back(i);
        v2.push_back(b / i);
      }
    }
    // Try each pair of divisors
    for (auto i : v1)
      for (auto j : v2) {
        k = i * j;
        // Compute x = smallest multiple of k that is > a
        r1 = (a / k + 1) * k;
        if (r1 > c)
          continue;
        // Compute y = smallest multiple of (a * b / k) that is > b
        r2 = (b / (a * b / k) + 1) * (a * b / k);
        if (r2 > d)
          continue;
        cout << r1 << ' ' << r2 << '\n';
        goto z;
      }
    cout << "-1 -1\n";
  z:;
  }
}


// https://github.com/VaHiX/CodeForces/