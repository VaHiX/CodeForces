// Problem: CF 1316 A - Grade Allocation
// https://codeforces.com/contest/1316/problem/A

/*
 * Problem: A. Grade Allocation
 * Purpose: Maximize the score of student 1 while satisfying constraints:
 *          - All scores are integers between 0 and m
 *          - Average score of class remains unchanged
 * Algorithms/Techniques: Greedy approach
 * Time Complexity: O(n) per test case, where n is number of students
 * Space Complexity: O(1), only using a few variables
 */

#include <cstdio>
int main() {
  long t; // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    long n, m; // n = number of students, m = maximum possible score
    scanf("%ld %ld", &n, &m);
    long long s(0); // s = sum of all current scores
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // Accumulate total score
    }
    // Output maximum possible score for student 1:
    // Either the total sum (if it's <= m), or m (if we're constrained by upper bound)
    printf("%ld\n", (s < m) ? s : m);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/