// Problem: CF 1676 H2 - Maximum Crossings (Hard Version)
// https://codeforces.com/contest/1676/problem/H2

/*
 * Problem: Maximum Crossings (Hard Version)
 * 
 * Algorithm: Binary Indexed Tree (Fenwick Tree) 
 * 
 * Approach:
 * - For each wire from segment i of the top terminal to segment a[i] of the bottom terminal,
 *   we want to count how many previously placed wires cross with it.
 * - A wire from i to a[i] crosses another wire from j to a[j] if and only if:
 *   (i < j and a[i] > a[j]) or (i > j and a[i] < a[j]).
 * - To efficiently count such crossings, we use a BIT (Fenwick Tree).
 * - Traverse segments from right to left (i = n-1 down to 0).
 * - For each segment i:
 *   - Query how many previous segments have value < a[i] (to count crossings from the left)
 *   - Update BIT with a[i] to mark that segment i is now placed.
 * 
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) for the BIT array
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n, ans = 0;
    cin >> n;
    vector<int> a(n), T(n + 1);  // T is the Binary Indexed Tree (Fenwick Tree)
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = n - 1; i >= 0; i--) {
      // Query how many elements already placed have value < a[i]
      for (int x = a[i]; x > 0; x -= x & -x)
        ans += T[x];
      // Update BIT to mark that a[i] is now placed
      for (int x = a[i]; x <= n; x += x & -x)
        T[x] += 1;
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/