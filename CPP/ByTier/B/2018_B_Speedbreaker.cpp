// Problem: CF 2018 B - Speedbreaker
// https://codeforces.com/contest/2018/problem/B

/*
B. Speedbreaker
Algorithms/Techniques: Two-pointers, prefix/suffix analysis, greedy
Time Complexity: O(n) per test case
Space Complexity: O(n) for auxiliary arrays

The problem asks to count how many starting cities allow conquering all cities within their deadlines,
where each city can only be conquered if adjacent to a previously conquered city.

This solution uses the idea of tracking leftmost and rightmost positions for each value in array a,
and then uses prefix/suffix checks to determine valid starting points.
*/

#include <algorithm>
#include <iostream>

using namespace std;
#define N 1050500
int a[N], L[N], R[N], c[N];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int ql = n + 1, qr = 0, tag = 1, ansl = 1, ansr = n;
    for (int i = 1; i <= n; ++i)
      L[i] = n + 1, R[i] = 0; // Initialize left and right boundaries for each number
    for (int i = 1; i <= n; ++i)
      cin >> a[i], L[a[i]] = min(L[a[i]], i), R[a[i]] = max(R[a[i]], i),
                   ansl = max(ansl, i - a[i] + 1), // Find minimum time needed to reach current city
                   ansr = min(ansr, i + a[i] - 1); // Find maximum time allowed to reach current city
    for (int i = 1; i <= n; ++i) {
      ql = min(ql, L[i]); // Minimum left boundary seen so far
      qr = max(qr, R[i]); // Maximum right boundary seen so far
      if (qr - ql + 1 > i) // If current window exceeds index count, impossible to proceed
        tag = 0;
    }
    cout << (ansr - ansl + 1) * tag << "\n"; // Output number of valid starting cities
  }
}


// https://github.com/VaHiX/codeForces/