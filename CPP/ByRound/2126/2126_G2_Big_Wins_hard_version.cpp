// Problem: CF 2126 G2 - Big Wins!  (hard version)
// https://codeforces.com/contest/2126/problem/G2

/*
G2. Big Wins! (hard version)
Algorithm: Two-pointer with Disjoint Set Union (DSU) and sorting
Time Complexity: O(n log n) per test case due to sorting and DSU operations
Space Complexity: O(n) for arrays and auxiliary structures

This problem requires finding a subarray such that the difference between
its median and minimum element is maximized. The approach uses a reverse
processing of elements from largest to smallest, using DSU to track
connected components in both directions (left and right). For each element,
we compute how far we can extend to the left and right while respecting
the constraints for maximum median.

*/
#include <algorithm>
#include <iostream>
using namespace std;
int a[200001], dsu[2][200001], q[200001], m, n, r, s, t;
bool v[2][200001];
bool cmp(int i, int j) { return a[i] == a[j] ? i < j : a[i] < a[j]; }
int find(int w, int x) {
  return dsu[w][x] == x ? dsu[w][x] : dsu[w][x] = find(w, dsu[w][x]); // Find root with path compression
}
int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n;
    r = 0;
    m = 1000000000;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      q[i] = i;
      dsu[0][i] = i;
      dsu[1][i] = i;
      v[0][i] = 0;
      v[1][i] = 0;
    }
    sort(q + 1, q + n + 1, cmp); // Sort indices based on their values
    for (int i = n; i >= 1; i--) {
      s = 2;
      if (!v[0][q[i]]) { // If not visited yet
        v[0][q[i]] = 1;
        m = min(a[q[i]], m); // Update minimum value seen so far
        s--;
      }
      for (int j = find(0, q[i]); j >= 2 && s >= 1; j = find(0, j - 1)) { // Traverse left
        if (!v[0][j - 1]) {
          v[0][j - 1] = 1;
          m = min(a[j - 1], m);
          s--;
        }
        dsu[0][j] = find(0, j - 1); // Union operation
      }
      s = 2;
      if (!v[1][q[i]]) { // If not visited yet
        v[1][q[i]] = 1;
        m = min(a[q[i]], m); // Update minimum value seen so far
        s--;
      }
      for (int j = find(1, q[i]); j <= n - 1 && s >= 1; j = find(1, j + 1)) { // Traverse right
        if (!v[1][j + 1]) {
          v[1][j + 1] = 1;
          m = min(a[j + 1], m);
          s--;
        }
        dsu[1][j] = find(1, j + 1); // Union operation
      }
      r = max(a[q[i]] - m, r); // Update maximum difference
    }
    cout << r << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/