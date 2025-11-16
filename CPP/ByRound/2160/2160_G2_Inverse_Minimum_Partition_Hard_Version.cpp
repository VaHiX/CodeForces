// Problem: CF 2160 G2 - Inverse Minimum Partition (Hard Version)
// https://codeforces.com/contest/2160/problem/G2

/*
Code Purpose:
This solution computes the sum of f(b) over all contiguous subsequences b of a given sequence a.
The function f(c) is defined as the minimum total cost of partitioning sequence c, where the cost of a subsequence is ceil(sum_of_elements / min_element).
The algorithm uses dynamic programming with a monotonic stack to efficiently calculate contributions of each element.

Algorithms/Techniques:
- Monotonic stack to maintain indices of elements in increasing order
- Dynamic programming with states based on the number of partitions
- Binary search to find relevant indices during state transitions
- Optimization via precomputed thresholds for different partition sizes

Time Complexity: O(n * 120) = O(n) per test case
Space Complexity: O(n * 120) = O(n) due to memoization table d
*/

#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
const int N = 4e5 + 100;
int n, a[N], s[N], tp, d[N][155];
int findx(int x) {
  int l = 1, r = tp + 1;
  while (l < r) {
    int mi = (l + r) >> 1;
    if (a[s[mi]] >= x) {
      r = mi;
    } else {
      l = mi + 1;
    }
  }
  return l;
}
signed main() {
  // Initialize the base case for DP
  for (int i = 0; i < 155; i++) {
    d[0][i] = 1;
  }
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    int as = 0;
    tp = 0;
    for (int i = 1; i <= n; i++) {
      // Maintain a monotonic increasing stack of indices
      while (tp && a[s[tp]] >= a[i]) {
        tp--;
      }
      tp++;
      s[tp] = i;
      // Precompute thresholds for different numbers of partitions
      int le = findx((a[i] - 1) / 2 + 1), li = findx((a[i] - 1) / 3 + 1);
      for (int j = 0; j <= 120; j++) {
        d[tp][j] = tp + 1;
        if (j) {
          // Update DP state based on three possible previous states
          d[tp][j] = min(d[tp][j], d[tp - 1][j - 1]);
          if (j > 1) {
            d[tp][j] = min(d[tp][j], d[le - 1][j - 2]);
            if (j > 2) {
              d[tp][j] = min(d[tp][j], d[li - 1][j - 3]);
            }
          }
          // Accumulate the contribution of this subproblem
          as += j * (s[d[tp][j - 1] - 1] - s[d[tp][j] - 1]);
        }
      }
    }
    cout << as << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/