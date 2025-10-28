// Problem: CF 1291 B - Array Sharpening
// https://codeforces.com/contest/1291/problem/B

/*
B. Array Sharpening

Purpose:
This program determines whether a given array can be made "sharpened" by decreasing any positive elements.
An array is sharpened if there exists a peak element such that elements before it are strictly increasing and elements after it are strictly decreasing.

Algorithms/Techniques:
- Preprocessing using two auxiliary arrays (left and right)
- Dynamic programming approach to check increasing/decreasing conditions

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Input Format:
- First line contains number of test cases t
- For each test case:
  - First line: array size n
  - Second line: n integers representing the array elements

Output Format:
- "Yes" if array can be made sharpened, "No" otherwise
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
    // left[p] will be true if elements from 0 to p form a strictly increasing sequence
    std::vector<long> left(n, 0), right(n, 0);
    for (long p = 0; p < n; p++) {
      left[p] = (p == 0 || left[p - 1]) && (a[p] >= p); // Check if current element can maintain increasing property
    }
    // right[p] will be true if elements from p to n-1 form a strictly decreasing sequence
    for (long p = n - 1; p >= 0; p--) {
      right[p] = (p == n - 1 || right[p + 1]) && (a[p] >= n - 1 - p); // Check if current element can maintain decreasing property
    }
    bool res(false);
    for (long p = 0; p < n && !res; p++) {
      res |= (left[p] && right[p]); // If both left and right conditions are satisfied at position p, array can be sharpened
    }
    puts(res ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/