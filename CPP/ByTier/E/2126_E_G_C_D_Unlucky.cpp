// Problem: CF 2126 E - G-C-D, Unlucky!
// https://codeforces.com/contest/2126/problem/E

/*
E. G-C-D, Unlucky!
Problem: Given two arrays p (prefix GCDs) and s (suffix GCDs), determine if there exists an array a such that p[i] = gcd(a[1], ..., a[i]) and s[i] = gcd(a[i], ..., a[n]).

Algorithms/Techniques:
- Prefix and suffix GCD validation
- GCD properties and divisibility checks

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

*/

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 5;
int t, n, m, a[N], b[N], f;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    f = 1;
    for (int i = 1; i <= n; i++)
      cin >> a[i];  // Read prefix GCD array
    for (int i = 1; i <= n; i++)
      cin >> b[i];  // Read suffix GCD array
    if (a[n] != b[1])  // Check if last prefix GCD equals first suffix GCD
      f = 0;
    for (int i = 1; i < n; i++) {
      if (a[i] % a[i + 1] != 0)  // Ensure prefix GCDs are non-increasing and divisible
        f = 0;
      if (b[i + 1] % b[i] != 0)  // Ensure suffix GCDs are non-decreasing and divisible
        f = 0;
    }
    for (int i = 1; i < n; i++) {
      if (__gcd(a[i], b[i + 1]) != a[n])  // Check compatibility of prefix and suffix GCDs at each position
        f = 0;
    }
    if (f == 0)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/