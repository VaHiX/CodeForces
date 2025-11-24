// Problem: CF 1187 C - Vasya And Array
// https://codeforces.com/contest/1187/problem/C

#include <iostream>

using namespace std;
int n, m, x[1005], y[1005], cnt, t, l, r, a[1005];
bool num[1005];
int main() {
  cin >> n >> m;
  while (m--) {
    cin >> t >> l >> r;
    if (t)
      for (int i = l; i < r; i++)
        num[i] = 1; // Mark positions that must be sorted
    else {
      cnt++; // Count of not-sorted intervals
      x[cnt] = l; // Store start of not-sorted interval
      y[cnt] = r; // Store end of not-sorted interval
    }
  }
  a[1] = n; // Initialize first element of array
  for (int i = 2; i <= n; i++) {
    if (num[i - 1])
      a[i] = a[i - 1]; // If previous position is marked as sorted, keep same value
    else
      a[i] = a[i - 1] - 1; // Otherwise decrease value
  }
  for (int i = 1; i <= cnt; i++)
    if (a[x[i]] == a[y[i]]) 
      return cout << "NO", 0; // Check if any not-sorted interval has same values at endpoints (which would indicate it's sorted)
  cout << "YES\n";
  for (int i = 1; i <= n; i++)
    cout << a[i] << " "; // Output the constructed array
}

// https://github.com/VaHiX/CodeForces/