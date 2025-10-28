// Problem: CF 1708 A - Difference Operations
// https://codeforces.com/contest/1708/problem/A

/*
 * Problem: Make all elements from index 2 to n equal to zero using allowed operations.
 * Algorithm: The operation allows subtracting previous element from current one.
 * Key Insight: For the transformation to be possible, all elements must be divisible by the first element.
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s;
    scanf("%ld", &s); // Read first element
    bool possible(true);
    for (long p = 1; p < n; p++) { // Iterate through remaining elements
      long x;
      scanf("%ld", &x);
      if (x % s) { // Check if current element is divisible by first
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/