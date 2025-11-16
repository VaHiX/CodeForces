// Problem: CF 1999 G1 - Ruler (easy version)
// https://codeforces.com/contest/1999/problem/G1

#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
int gcd(int a, int b) {
  if (a == 0)
    return b;
  return gcd(b % a, a);
}
void solve() {
  int low = 1, high = 1000;
  int a = low, b = high, p, t;
  while (a < b) {
    a = low + (high - low) / 3;   // Calculate the first third point
    b = low + (high - low) * 2 / 3; // Calculate the second third point
    cout << "? " << a << " " << b << "\n" << flush;  // Query the rectangle
    cin >> p;
    if (p == -1)
      return;
    t = a * b + a;   // This represents the expected result if x is in range [a, b)
    if (p > t) {     // If measured area is larger, x must be <= a
      high = a;
    } else if (p == t) {  // If measured area equals expected, x is in [a, b]
      low = a;
      high = b;
    } else {         // If measured area is smaller, x must be >= b
      low = b;
    }
  }
  cout << "! " << a + 1 << "\n" << flush;  // Output the found x value
}
int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/