// Problem: CF 2146 D1 - Max Sum OR (Easy Version)
// https://codeforces.com/contest/2146/problem/D1

/*
D1. Max Sum OR (Easy Version)
Algorithms/Techniques: Bit manipulation, greedy approach, bit reversal pattern
Time Complexity: O(r * log r) per test case
Space Complexity: O(r) for storing the array

This problem asks to maximize the sum of bitwise ORs between two arrays a and b,
where b is fixed as [l, l+1, ..., r] and a can be reordered arbitrarily.
The approach involves reordering a optimally such that we maximize the OR operations.
The solution leverages bit manipulation and a pattern of swapping elements from
the ends toward the center using bit levels (powers of 2) to achieve optimal grouping.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define int long long
#define endl '\n'
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int l, r;
    cin >> l >> r;
    int tr = r;
    vector<int> a(r + 1);
    for (int i = 0; i <= r; i++) {
      a[i] = i;
    }
    int ans = 0;
    while (r > 0) {
      int k = 1 << __lg(r); // Find the highest power of 2 <= r
      int kk = k - 1;       // Start from the last element in current level
      for (int i = k; i <= r; i++, kk--) {
        ans += (a[i] | a[kk]) * 2; // Add OR result, multiplied by 2 because of symmetry
        swap(a[i], a[kk]);         // Swap to move elements toward optimal pairing
      }
      r = kk; // Reduce the range for next iteration
    }
    cout << ans << endl;
    for (int i = 0; i <= tr; i++) {
      cout << a[i] << " ";
    }
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/