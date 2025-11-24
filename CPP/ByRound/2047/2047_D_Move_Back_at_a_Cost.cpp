// Problem: CF 2047 D - Move Back at a Cost
// https://codeforces.com/contest/2047/problem/D

/*
D. Move Back at a Cost
Algorithms/Techniques: Greedy, Simulation, Sorting

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the arrays a and f

The problem requires transforming an array using specific operations to achieve the lexicographically smallest result. 
The key idea is to greedily increase elements that are greater than any element to their right, ensuring minimal impact on the overall order.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int t, n, a[100005], mn, mnn, f[100005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    mn = mnn = 2e9; // Initialize min values
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      f[i] = 0; // Reset flag array
    }
    for (int i = n - 1; i >= 0; i--) {
      if (mn > a[i])
        mn = a[i]; // Track minimum seen so far from the right
      if (a[i] > mn) { // If current element is greater than min, increment it and mark
        a[i]++;
        f[i] = 1;
        mnn = min(mnn, a[i]); // Keep track of smallest increased value
      }
    }
    for (int i = n - 1; i >= 0; i--)
      if (f[i] == 0 && a[i] > mnn) // If not marked and greater than min increased value, increment
        a[i]++;
    sort(a, a + n); // Sort to get lexicographically smallest arrangement
    for (int i = 0; i < n; i++)
      cout << a[i] << " ";
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/