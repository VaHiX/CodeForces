// Problem: CF 1584 C - Two Arrays
// https://codeforces.com/contest/1584/problem/C

/*
C. Two Arrays
Algorithm: Sort both arrays and check if each element in b can be matched to an element in a
by adding 0 or 1. This works because we can only add 1 to elements, so the difference
between elements in b and a must be 0 or 1.

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the arrays

The problem allows us to:
1. Add 1 to any subset of elements in array a (k operations)
2. Then rearrange a to match b exactly

Key Insight:
After sorting both arrays, if we can match each element in b with an element in a such that:
b[i] >= a[i] AND b[i] <= a[i] + 1,
then it's possible to transform a into b.
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
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(a.begin(), a.end()); // Sort array a
    sort(b.begin(), b.end()); // Sort array b
    bool res(true);
    for (long p = 0; p < n; p++) {
      if (b[p] < a[p] || b[p] > a[p] + 1) { // Check if element in b can be formed from a
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/