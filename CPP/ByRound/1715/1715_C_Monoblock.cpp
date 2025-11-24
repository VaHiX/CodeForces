// Problem: CF 1715 C - Monoblock
// https://codeforces.com/contest/1715/problem/C

/*
 * Problem: Monoblock - Calculate sum of awesomeness for all subsegments after each update
 * 
 * Algorithms/Techniques:
 * - Preprocessing: For each element, compute the contribution to the total sum using a function f(i)
 * - Incremental Update: When an element changes, only recompute the contributions of affected segments
 * 
 * Time Complexity: O(n + m), where n is array length and m is number of queries
 * Space Complexity: O(n), for storing the array
 * 
 * The function f(i) computes how much the i-th element contributes to the total awesomeness sum.
 * It considers the current value and its neighbors to determine block boundaries.
 */

#include <iostream>

#define int long long
using namespace std;
int n, q;
int a[100005];
int f(int x) {
  int l = n - x + 1;
  // If current element is same as previous one, it reduces the number of blocks
  if (a[x] == a[x - 1]) {
    return l;
  }
  // Otherwise, it increases the number of blocks
  return x * l;
}
signed main() {
  cin >> n >> q;
  int sum = 0;
  // Preprocessing step: compute initial total awesomeness sum
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += f(i);
  }
  // Process each query
  while (q--) {
    int x, y;
    cin >> x >> y;
    // Remove contribution of old value
    sum -= f(x) + f(x + 1);
    a[x] = y;
    // Add contribution of new value
    sum += f(x) + f(x + 1);
    cout << sum << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/