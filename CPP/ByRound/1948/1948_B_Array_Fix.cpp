// Problem: CF 1948 B - Array Fix
// https://codeforces.com/contest/1948/problem/B

/*
B. Array Fix
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1), only using a constant amount of extra space.

Algorithm/Techniques:
- Greedily process elements from left to right.
- For each element:
  - If it's less than 10, compare it with the previous valid number.
  - If it's >= 10, split into digits and try to place them appropriately to maintain non-decreasing order.
- Keep track of the last valid element (could be a digit from a split number).
- Use an intuitive approach: if we can place current element without breaking order, do so;
  otherwise, check if it's possible to split and fit in between.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(-1); // Tracks the last valid element processed
    bool res(true); // Flag indicating whether array can be sorted
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      int d(x / 10), m(x % 10); // Extract tens and units digit of x
      if (prev <= d && d <= m) {
        // If we can place d between prev and m (which is a valid split)
        prev = m;
      } else if (prev <= x) {
        // We can insert x itself as it's >= prev
        prev = x;
      } else {
        // Neither splitting nor inserting x maintains order -> impossible
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/