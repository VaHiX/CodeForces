// Problem: CF 449 A - Jzzhu and Chocolate
// https://codeforces.com/contest/449/problem/A

/*
Code Purpose:
This code solves the problem of cutting a chocolate bar of size n×m exactly k times to maximize the area of the smallest piece.
The strategy involves:
- If k is greater than n + m - 2, it's impossible to make k cuts.
- Otherwise, we try to make cuts optimally to maximize the minimum piece area.
- We consider two cases:
  1. If k < m, we make horizontal cuts to maximize area.
  2. If k >= m, we make vertical cuts to maximize area.

Algorithm:
- Greedy approach with mathematical analysis.
- Time Complexity: O(1)
- Space Complexity: O(1)

*/
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long int ll;
ll n, m, k, ans = 0;
int main() {
  cin >> n >> m >> k;
  // Ensure n <= m for easier handling
  if (n > m) {
    ll t = n;
    n = m;
    m = t;
  }
  // If k exceeds maximum possible cuts, impossible to cut
  if (k > n + m - 2) {
    cout << -1 << endl;
    return 0;
  }
  // If k is less than m, we can cut horizontally to maximize result
  if (k < m)
    cout << max(m / (k + 1) * n, n / (k + 1) * m) << endl;
  else
    // Otherwise, we cut vertically to maximize result
    cout << (n / (k + 2 - m)) << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/