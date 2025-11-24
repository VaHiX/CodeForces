// Problem: CF 1133 C - Balanced Team
// https://codeforces.com/contest/1133/problem/C

/*
C. Balanced Team
Algorithm: Two Pointers + Sorting
Time Complexity: O(n log n) due to sorting; two pointers traverse once -> O(n)
Space Complexity: O(n) for the vector storing input

Problem:
You are given n students with programming skills. Create a team with maximum number of students such that
the difference between any pair of students' skills is at most 5.

Approach:
1. Sort the array of skills.
2. Use two pointers technique:
   - Left pointer (ind) tracks the start of valid window
   - Right pointer (p) iterates through the array
   - For each right pointer, adjust left pointer until difference <= 5
   - Track maximum size of such window
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the skills to enable two-pointer technique
  long ind(0), mx(0);
  for (long p = 0; p < n; p++) {
    while (a[ind] + 5 < a[p]) { // Shrink window from left until difference <= 5
      ++ind;
    }
    long cur = p - ind + 1; // Current size of valid window
    mx = (mx > cur) ? mx : cur; // Update maximum window size
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/