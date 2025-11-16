// Problem: CF 1999 G2 - Ruler (hard version)
// https://codeforces.com/contest/1999/problem/G2

#include <iostream>

using namespace std;
const int MAX = 200'007;
const int MOD = 1'000'000'007;
void solve() {
  // Binary search with ternary search approach to find the missing number x
  // The idea is to use queries on rectangles to determine the range where x lies
  int l = 1, r = 999;
  while (r - l > 2) {
    // Calculate two midpoints for ternary search
    int a = (2 * l + r) / 3;
    int b = (2 * r + l) / 3;
    // Query the rectangle with dimensions a x b
    cout << "? " << a << ' ' << b << endl;
    int resp;
    cin >> resp;
    // If the result matches (a+1)*(b+1), then x is in the left portion
    if (resp == (a + 1) * (b + 1)) {
      r = a;
    } else if (resp == a * b) {
      // If the result matches a*b, then x is in the right portion
      l = b;
    } else {
      // Otherwise x is in the middle portion
      l = a;
      r = b;
    }
  }
  // Handle the last few elements with a binary search step
  if (r - l == 2) {
    // Query a specific rectangle to decide between l+1 and l+2
    cout << "? 1 " << l + 1 << endl;
    int resp;
    cin >> resp;
    // If the result is l+1, x is l+1, else x is l+2
    if (resp == l + 1) {
      l = l + 1;
    } else {
      r = l + 1;
    }
  }
  // Output the final result
  cout << "! " << r << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  for (int i = 1; i <= tt; i++) {
    solve();
  }
}

// https://github.com/VaHiX/CodeForces/