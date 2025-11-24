// Problem: CF 1807 G1 - Subsequence Addition (Easy Version)
// https://codeforces.com/contest/1807/problem/G1

/*
G1. Subsequence Addition (Easy Version)
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: Greedy approach
- Sort the array first.
- Initialize sum = 1 (since initial array is [1])
- For each element in sorted array:
  - If current sum < element, return "NO"
  - Else, add element to sum
- If all elements are processed successfully, return "YES"

Time Complexity: O(n log n) due to sorting; for each test case, the loop runs in O(n)
Space Complexity: O(n) for storing the input array

The problem is essentially checking whether a given sequence can be generated
from the initial array [1] using the allowed operations (adding sum of any subsequence).
This can be solved greedily by observing that at each step, we need to be able to form
the next largest number using previously formed numbers.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n, 0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    bool ans(a[0] == 1);  // First element must be 1 to start with initial array [1]
    long long s(1);       // Start with sum = 1 (initial array has one element: 1)
    for (long p = 1; ans && p < n; p++) {
      if (s < a[p]) {     // If we cannot form a[p] using current sum, impossible
        ans = false;
      } else {
        s += a[p];        // Add a[p] to our reachable sum
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/