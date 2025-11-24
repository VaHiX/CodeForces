// Problem: CF 1973 B - Cat, Fox and the Lonely Array
// https://codeforces.com/contest/1973/problem/B

/*
Purpose: This code determines the "loneliness" of an array, which is the smallest positive integer k such that all subarrays of length k have the same bitwise OR value.

Algorithm:
1. For each bit position from 0 to 20 (since elements are less than 2^20), we find the maximum gap between consecutive elements that have that bit set.
2. The loneliness k is the maximum of these gaps across all bit positions.
3. We also consider the gap from the last set bit to the end of the array.

Time Complexity: O(n * 20) = O(n) since 20 is a constant
Space Complexity: O(1) as we use only a few variables and a fixed-size vector for input

Techniques:
- Bit manipulation to process each bit independently
- Two-pointer approach to track gaps between set bits
- Efficient update of maximum gap using chkmax helper function

*/
#include <stddef.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>

using namespace std;
#define endl "\n"
template <class T, class T2> inline bool chkmax(T &x, const T2 &y) {
  return x < y ? x = y, 1 : 0;
}
template <class T, class T2> inline bool chkmin(T &x, const T2 &y) {
  return x > y ? x = y, 1 : 0;
}
#ifndef LOCAL
#define cerr                                                                   \
  if (false)                                                                   \
  cerr
#endif
#define out(x) #x << " = " << x << "  "
template <typename T, typename S>
ostream &operator<<(ostream &os, const pair<T, S> &p) {
  return os << "(" << p.first << ", " << p.second << ")";
}
template <typename T, typename B = decay<decltype(*begin(declval<T>()))>,
          typename enable_if<!is_same<T, string>::value>::type * = nullptr>
ostream &operator<<(ostream &os, const T &c) {
  bool f = false;
  os << "(";
  for (const auto &x : c) {
    if (f) {
      os << ", ";
    }
    f = true;
    os << x;
  }
  return os << ")";
}
typedef long long ll;
const ll mod = 1e9 + 7;
const int MAX_N = 1e6 + 10;
void solve() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto &j : a)
    std::cin >> j;
  int nas = 1;  // Initialize result to 1 (minimum possible k)
  for (int bit = 0; bit <= 20; bit++) {  // For each bit position
    int lst = -1;  // Position of last element with current bit set
    for (int j = 0; j < n; j++) {  // Traverse array
      if (a[j] & (1 << bit)) {  // If current bit is set
        chkmax(nas, j - lst);  // Update max gap
        lst = j;  // Update last position
      }
    }
    cerr << out(bit) << out(lst) << endl;
    if (lst != -1)  // If at least one bit was set
      chkmax(nas, n - lst);  // Check gap from last set bit to end
  }
  std::cout << nas << endl;
}
signed main() {
#ifndef LOCAL
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/