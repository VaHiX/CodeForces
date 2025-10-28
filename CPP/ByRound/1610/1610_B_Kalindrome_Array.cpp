// Problem: CF 1610 B - Kalindrome Array
// https://codeforces.com/contest/1610/problem/B

/*
 * Problem: B. Kalindrome Array
 *
 * Purpose: Determine if an array is "kalindrome", which means it's possible to
 *          delete some elements equal to a certain value x such that the remaining
 *          array forms a palindrome.
 *
 * Algorithm:
 *   - Use two pointers from both ends of the array to find mismatched elements.
 *   - When a mismatch is found, save those values u and v (the left and right elements).
 *   - Try removing either u or v and check if the resulting array can form a palindrome.
 *   - If one of the removal strategies works, return "YES", otherwise "NO".
 *
 * Time Complexity: O(n) per test case. Each element is checked at most twice in the worst case
 * Space Complexity: O(n) for storing the input array
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
    long u(-1), v(-1);  // Store mismatched values
    long left(0), right(n - 1);
    while (left < right) {
      if (a[left] == a[right]) {
        ++left;
        --right;
      } else {
        u = a[left];   // Mismatched left value
        v = a[right];  // Mismatched right value
        break;
      }
    }
    bool possibleA(true), possibleB(true);
    left = 0, right = n - 1;
    while (u > 0 && left < right) {
      if (a[left] == a[right]) {
        ++left;
        --right;
      } else if (a[left] == u) {
        ++left;
      } else if (a[right] == u) {
        --right;
      } else {
        possibleA = false;
        break;
      }
    }
    left = 0, right = n - 1;
    while (v > 0 && left < right) {
      if (a[left] == a[right]) {
        ++left;
        --right;
      } else if (a[left] == v) {
        ++left;
      } else if (a[right] == v) {
        --right;
      } else {
        possibleB = false;
        break;
      }
    }
    bool possible = possibleA || possibleB;
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/