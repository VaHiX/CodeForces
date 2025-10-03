// Problem: CF 2110 F - Faculty
// https://codeforces.com/contest/2110/problem/F

/*
F. Faculty
time limit per test2 seconds
memory limit per test256 megabytes

This problem asks to compute the "beauty" of prefixes of an array, where beauty is defined as the maximum value of f(a[i], a[j]) over all pairs in the prefix, where f(x, y) = (x % y) + (y % x).

Algorithms/Techniques:
- Greedy approach with maintaining maximum element seen so far
- Preprocessing to avoid recalculating all pairs each time
- Efficient computation by leveraging properties of mod operation

Time Complexity: O(n) amortized per test case, since each element is processed at most twice in the loop.
Space Complexity: O(n) for storing the input array.

*/

#include <algorithm>
#include <iostream>

using namespace std;

int t, n, a[1000100];

// Function to compute f(x, y) = (x % y) + (y % x)
int find(int x, int y) { return x % y + y % x; }

int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    
    int ansn = 0, maxn = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] > maxn) {
        // If current element is greater than the previous maximum
        if (a[i] >= maxn * 2) {
          // Update maximum only if it's at least twice as large
          maxn = a[i];
          for (int j = 1; j <= i; j++)
            ansn = max(ansn, find(a[j], a[i]));  // Re-calculate answer considering new max
        } else {
          // If not significantly larger, just update max and set ansn to a[i]
          maxn = a[i];
          ansn = a[i];
        }
      } else {
        // Current element is not greater than maxn, so we can just check against it
        ansn = max(ansn, find(maxn, a[i]));
      }
      cout << ansn << " ";
    }
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/