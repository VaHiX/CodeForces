// Problem: CF 1690 B - Array Decrements
// https://codeforces.com/contest/1690/problem/B

/*
B. Array Decrements
Algorithm: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing arrays a and b

The problem allows decrementing all non-zero elements of array 'a' in each operation.
We need to determine if we can transform array 'a' into array 'b' using these operations.

Key Insight:
- For each element, if b[i] > a[i], it's impossible (we can only decrease).
- The maximum difference (a[i] - b[i]) tells us the minimum number of operations needed.
- In all operations, we must reduce all non-zero elements by 1.
- This means that for any position where b[i] != 0 and diff < max_diff, it is not possible to achieve b[i].
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    bool possible(true);
    long mxd(-1);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
      if (b[p] > a[p]) {
        possible = false;
      }
      long diff = a[p] - b[p];
      mxd = (mxd > diff) ? mxd : diff;
    }
    for (long p = 0; possible && p < n; p++) {
      long diff = a[p] - b[p];
      if (diff < mxd && b[p] != 0) {
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/