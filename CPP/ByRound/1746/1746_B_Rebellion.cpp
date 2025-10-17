// Problem: CF 1746 B - Rebellion
// https://codeforces.com/contest/1746/problem/B

/*
B. Rebellion
Algorithm: Two-pointer approach
Time Complexity: O(n) amortized per test case
Space Complexity: O(n) for the vector storage

The problem asks to find the minimum number of operations to make an array of 0s and 1s non-decreasing.
Each operation allows moving a value from one index to another, effectively adding to the target element.

Approach:
- Use two pointers (left and right) starting from both ends of the array
- Move left pointer forward while encountering 0s
- Move right pointer backward while encountering 1s
- When we find a 0 on the left and a 1 on the right, an operation is needed to move the 0 to the right
- Continue until pointers meet or cross
- This counts the minimum number of mismatches that need to be fixed.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<int> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%d", &v[p]);
    }
    long left(0), right(n - 1), cnt(0);
    while (left < right) {
      while (v[left] == 0) {   // Skip consecutive zeros from the left
        ++left;
      }
      while (v[right] == 1) {  // Skip consecutive ones from the right
        --right;
      }
      if (left < right) {      // If valid pair exists, perform operation
        ++cnt;
      } else {
        break;               // No more operations possible
      }
      ++left;                  // Move left pointer forward
      --right;                 // Move right pointer backward
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/