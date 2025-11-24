// Problem: CF 1399 A - Remove Smallest
// https://codeforces.com/contest/1399/problem/A

/*
Problem: A. Remove Smallest
Algorithm: Sort and check if consecutive elements differ by at most 1
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage

This problem asks whether we can reduce an array to a single element by repeatedly
removing the smaller of two elements whose absolute difference is <= 1.
The key insight is that after sorting, we only need to check if each element
is at most 1 greater than the previous one. If so, we can always perform operations
to reduce the array to a single element.

Sample Input:
5
3
1 2 2
4
5 5 5 5
3
1 2 4
4
1 3 4 4
1
100

Sample Output:
YES
YES
NO
NO
YES
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
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort the array to simplify checking consecutive differences
    bool res(true);
    for (long p = 1; p < n; p++) {
      if (a[p - 1] + 1 < a[p]) { // If difference is more than 1, impossible to reduce
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/