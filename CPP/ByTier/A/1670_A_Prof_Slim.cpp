// Problem: CF 1670 A - Prof. Slim
// https://codeforces.com/contest/1670/problem/A

/*
 * Problem: Determine if an array can be sorted by swapping signs of elements with different signs.
 *
 * Algorithm:
 * 1. Count negative numbers in the array.
 * 2. Process the first 'neg' elements (all negatives after sign changes).
 *    - If current element is positive, flip its sign.
 *    - Ensure the modified sequence remains non-decreasing.
 * 3. Process the rest of the elements (positive ones).
 *    - If current element is negative, flip its sign.
 *    - Ensure the modified sequence remains non-decreasing.
 * 4. Return YES if entire array can be made non-decreasing, otherwise NO.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
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
    long neg(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      neg += (a[p] < 0); // Count negative numbers
    }
    bool res(true);
    long prev = -1e9 - 7;
    for (long p = 0; res && p < neg; p++) {
      if (a[p] >= 0) {
        a[p] = -a[p]; // Flip sign of positive number to negative
      }
      if (a[p] < prev) {
        res = false;
        break;
      }
      prev = a[p];
    }
    for (long p = neg; res && p < n; p++) {
      if (a[p] <= 0) {
        a[p] = -a[p]; // Flip sign of negative number to positive
      }
      if (a[p] < prev) {
        res = false;
        break;
      }
      prev = a[p];
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/