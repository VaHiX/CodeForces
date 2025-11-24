// Problem: CF 1741 D - Masha and a Beautiful Tree
// https://codeforces.com/contest/1741/problem/D

/*
Algorithm/Technique: 
The approach is based on a recursive-like strategy applied level by level from bottom to top of the complete binary tree.
Each level corresponds to a step where we compare pairs of elements that are at a distance of k (which doubles each step).
If the elements are out of order (i.e., a[i] > a[i + k]), we swap them and increment the operation count.
We also check if there's an inversion in the arrangement using a helper condition:
abs(a[i] - a[i + k]) != k checks if elements are correctly spaced for a valid permutation in the current level.
If any inversion is detected, we return -1.

Time Complexity: O(m * log m)
Space Complexity: O(m)
*/
#include <stdlib.h>
#include <iostream>
#include <utility>

using namespace std;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int q;
  cin >> q;
  while (q--) {
    int m;
    cin >> m;
    int a[m];
    for (int &i : a)
      cin >> i;
    bool inv = 0;
    int cnt = 0;
    for (int k = 1; k < m; k <<= 1) {
      for (int i = 0; i < m; i += 2 * k) {
        // Check if the current pair of elements satisfies the condition to be in order
        if (abs(a[i] - a[i + k]) != k)
          inv = 1;
        // Swap if elements are out of order
        if (a[i] > a[i + k]) {
          swap(a[i], a[i + k]);
          cnt++;
        }
      }
    }
    cout << (inv ? -1 : cnt) << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/