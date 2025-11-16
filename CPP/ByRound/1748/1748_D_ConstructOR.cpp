// Problem: CF 1748 D - ConstructOR 
// https://codeforces.com/contest/1748/problem/D

#include <iostream>

#define int long long
using namespace std;
int t, a, b, d, k, x;
void sol() {
  cin >> a >> b >> d;
  k = x = 0;
  // Find the position of the lowest set bit in d
  while ((d >> k & 1) ^ 1)
    k++;
  // Iterate through all bits up to 30
  for (int i = 0; i < 30; i++) {
    // Check if the i-th bit is set in (a | b) and not in x
    if (((a | b) >> i & 1) && (x >> i & 1) == 0) {
      // If i is less than k, it's impossible to satisfy the condition
      if (i < k) {
        cout << "-1\n";
        return;
      } else
        // Set the corresponding bit in x to make the condition true
        x += (d << i - k);
    }
  }
  cout << x << '\n';
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--)
    sol();
}


// https://github.com/VaHiX/CodeForces/