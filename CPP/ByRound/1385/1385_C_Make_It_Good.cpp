// Problem: CF 1385 C - Make It Good
// https://codeforces.com/contest/1385/problem/C

/*
C. Make It Good

Purpose:
This code determines the minimum length of a prefix to remove from an array to make it "good".
An array is considered good if we can construct a non-decreasing sequence by repeatedly taking elements
from either the front or the back of the array.

Algorithm:
- Traverse the array from right to left to find the point where the sequence starts violating
  the conditions for being good.
- The logic uses a state flag to track whether we are in a "decreasing" phase or a "non-decreasing" phase.
- The solution identifies the earliest index (from the left) where removing elements would leave
  a good array.

Time Complexity: O(n) per test case, as we traverse the array once.
Space Complexity: O(n) for storing the input array.

Sample Input:
5
4
1 2 3 4
7
4 3 3 8 4 5 2
3
1 1 1
7
1 3 1 4 5 3 2
5
5 4 3 2 3

Sample Output:
0
4
0
2
3
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
    long rem(0);                  // Stores the index from which to start removing elements
    bool state(0);                // State flag: 0 means we're in a non-decreasing phase, 1 means decreasing
    for (long p = n - 2; p >= 0; p--) {
      if (!state && a[p] >= a[p + 1]) {
        continue;                 // Still in non-decreasing; keep going
      } else if (!state && a[p] <= a[p + 1]) {
        state = true;             // Transition to decreasing phase
      } else if (state && a[p] <= a[p + 1]) {
        continue;                 // In decreasing phase, still valid
      } else if (state && a[p] > a[p + 1]) {
        rem = p + 1;              // Found the point where sequence breaks good property
        break;
      }
    }
    printf("%ld\n", rem);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/