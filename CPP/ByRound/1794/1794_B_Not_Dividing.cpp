// Problem: CF 1794 B - Not Dividing
// https://codeforces.com/contest/1794/problem/B

/*
Purpose: This code solves the "Not Dividing" problem where we need to adjust an array such that no element is divisible by its predecessor, using at most 2n operations.

Algorithm/Techniques:
- Greedy approach: For each element, if it's divisible by the previous element, increment it by 1.
- Special case handling for 1: If an element is 1, it's changed to 2 to avoid division issues.
- Time and Space Complexity:
  - Time Complexity: O(n) per test case, where n is the size of the array.
  - Space Complexity: O(n) for storing the array.
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
      if (a[p] == 1) {
        a[p] = 2;  // Special case: 1 is divisible by everything, so change to 2
      }
      if (p && a[p] % a[p - 1] == 0) {
        ++a[p];  // If current element is divisible by previous, increment it
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/