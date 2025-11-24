// Problem: CF 1305 A - Kuroni and the Gifts
// https://codeforces.com/contest/1305/problem/A

/*
Code Purpose:
This program takes multiple test cases, each consisting of n necklaces and n bracelets with distinct brightness values.
For each test case, it sorts both the necklace and bracelet brightness arrays in ascending order and prints them.
The task is to assign one necklace and one bracelet to each daughter such that all total brightness sums are distinct.
However, the current implementation only sorts and prints the arrays without creating valid assignments.

Algorithms/Techniques:
- Sorting using std::sort
- Simple iteration and input/output handling

Time Complexity:
O(n * log(n)) per test case due to sorting, where n is the number of daughters/necklaces/bracelets.

Space Complexity:
O(n) for storing the arrays a and b.

Note: The current implementation does not solve the full problem of assigning gifts such that sums are distinct.
It only performs the sorting step as described in the original code.
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
    sort(a.begin(), a.end()); // Sort necklaces in ascending order
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    };
    puts("");
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(b.begin(), b.end()); // Sort bracelets in ascending order
    for (long p = 0; p < n; p++) {
      printf("%ld ", b[p]);
    };
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/