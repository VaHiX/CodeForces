// Problem: CF 1945 H - GCD is Greater
// https://codeforces.com/contest/1945/problem/H

/*
Code Purpose:
This code solves a game problem where Kirill and Anton choose subsets of an array to determine a winner based on GCD and bitwise AND operations. 
The algorithm evaluates potential winning strategies by:
1. Checking for specific bit patterns that may lead to a win
2. Using prefix and suffix arrays to efficiently compute bitwise ANDs
3. Attempting to find pairs of elements that satisfy the winning condition
4. Falling back to a general checking method if specific patterns fail

Algorithms/Techniques:
- Bit manipulation and bitwise AND computation using prefix/suffix arrays
- GCD calculations using built-in __gcd function
- Optimization with bit pattern analysis
- Greedy selection of elements for subsets

Time Complexity: O(n * log(MaxValue)) where n is the array size and MaxValue is the maximum element in the array
Space Complexity: O(n + MaxValue) for storing arrays and auxiliary data

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
const int N = 4e5 + 10;
int a[N], pre[N], suf[N], c[N], v[N], n, x;
bool check(int p) {
  // Initialize prefix AND array with all 1s (identity for AND)
  pre[0] = (1 << 23) - 1;
  // Initialize suffix AND array with all 1s (identity for AND)
  suf[n + 1] = (1 << 23) - 1;
  // Compute prefix AND values
  for (int i = 1; i <= n; i++) {
    pre[i] = i == p ? pre[i - 1] : pre[i - 1] & a[i];
  }
  // Compute suffix AND values
  for (int i = n; i; i--) {
    suf[i] = i == p ? suf[i + 1] : suf[i + 1] & a[i];
  }
  // Check if choosing element at position p gives a winning condition
  for (int i = 1; i <= n; i++) {
    if (i == p)
      continue;
    // Compute GCD of the chosen element and the current element
    int d = __gcd(a[p], a[i]), w = pre[i - 1] & suf[i + 1];
    // Check if condition is satisfied: GCD > (AND of remaining elements + x)
    if (d > w + x) {
      cout << "YES\n";
      cout << 2 << ' ' << a[i] << ' ' << a[p] << '\n';
      cout << n - 2 << ' ';
      for (int j = 1; j <= n; j++) {
        if (j != i && j != p)
          cout << a[j] << ' ';
      }
      cout << '\n';
      return true;
    }
  }
  return false;
}
void solve() {
  cin >> n >> x;
  int Max = 0;
  int sand = (1 << 23) - 1; // Initialize to all bits set
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    Max = max(Max, a[i]);
    sand &= a[i]; // Find AND of all elements
  }
  // Reset counting arrays
  for (int i = 1; i <= Max; i++)
    c[i] = 0;
  for (int i = 1; i <= n; i++)
    v[i] = 0;
  // Check bit patterns from highest to lowest
  for (int k = 19; ~k; k--) {
    int z = 0;
    for (int i = 1; i <= n; i++)
      z += !(a[i] >> k & 1); // Count elements with 0 at bit k
    if (z == 1 || z == 2) { // If only 1 or 2 elements have 0 at bit k
      for (int i = 1; i <= n; i++) {
        if (!(a[i] >> k & 1)) {
          v[i] = 1; // Mark elements with 0 at bit k
          if (check(i))
            return; // Try to use this element to win
        }
      }
    }
  }
  vector<int> S;
  for (int i = 1; i <= n; i++)
    if (!v[i])
      S.emplace_back(i), c[a[i]]++; // Collect unmarked elements for later processing

  // Check GCD conditions for larger values
  for (int d = Max; d > sand + x; d--) {
    int cnt = 0;
    for (int i = d; i <= Max; i += d)
      cnt += c[i]; // Count multiples of d
    if (cnt > 1) { // If there are more than one multiple
      int p1 = 0, p2 = 0;
      for (int p : S) {
        if (a[p] % d == 0) {
          if (!p1)
            p1 = p;
          else if (!p2)
            p2 = p;
        }
      }
      cout << "YES\n";
      cout << 2 << ' ' << a[p1] << ' ' << a[p2] << '\n';
      cout << n - 2 << ' ';
      for (int i = 1; i <= n; i++) {
        if (i != p1 && i != p2)
          cout << a[i] << ' ';
      }
      cout << '\n';
      return;
    }
  }
  cout << "NO\n";
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/