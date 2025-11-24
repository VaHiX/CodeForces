// Problem: CF 1998 A - Find K Distinct Points with Fixed Center
// https://codeforces.com/contest/1998/problem/A

#include <iostream>

using namespace std;
int query(int a, int b) {
  cout << "? " << a << " " << b << std::endl;
  int res;
  cin >> res;
  return res;
}
void solve() {
  int x, y, n;
  cin >> x >> y >> n;
  if (n % 2 == 1) {
    cout << x << " " << y << '\n'; // Output the center point if n is odd
    n--;
  }
  for (int i = 1; i <= n / 2; i++) {
    cout << x - i << " " << y << '\n'; // Output point to the left
    cout << x + i << " " << y << '\n'; // Output point to the right
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/