// Problem: CF 1848 C - Vika and Price Tags
// https://codeforces.com/contest/1848/problem/C

/*
 * Problem: C. Vika and Price Tags
 * 
 * Purpose:
 *   Determine whether a pair of arrays (a, b) is "dull", meaning that after applying a series of operations
 *   (where each operation computes absolute differences between elements of the arrays and swaps the arrays),
 *   the array 'a' eventually becomes all zeros.
 *
 * Algorithm:
 *   For each index i where at least one of the values a[i] or b[i] is non-zero:
 *     - Compute a sequence of values using the operation:
 *         x = a[i], y = b[i]
 *         Loop while x != 0:
 *           If x >= 2 * y and y != 0, then x = x % (2 * y)
 *           Else if y >= 2 * x, then y = y % (2 * x)
 *           Then update: (x, y) = (y, |y - x|)
 *     - Track the loop cycle (v) mod 3 for each index.
 *     - If a cycle is inconsistent with a previously seen one, output "NO".
 *     - If all indices are consistent, output "YES".
 *
 * Time Complexity: O(n)
 *   Each element goes through a loop proportional to log(max(a[i], b[i])), which is bounded, hence linear overall.
 *
 * Space Complexity: O(1)
 *   Only a constant amount of extra space is used, independent of input size.
 */

#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  int flag = 0;
  int t = -1;
  for (int i = 0; i < n; i++) {
    if (!a[i] && !b[i])
      continue;
    int x = a[i], y = b[i];
    int v = 0;
    while (x != 0) {
      if (x >= 2 * y && y)
        x %= 2 * y;
      else if (y >= 2 * x)
        y %= 2 * x;
      tie(x, y) = make_pair(y, abs(y - x));
      v = (v + 1) % 3;
    }
    if (t != -1 && t != v) {
      flag = 1;
      break;
    }
    t = v;
  }
  if (flag) {
    cout << "NO\n";
  } else
    cout << "YES\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/