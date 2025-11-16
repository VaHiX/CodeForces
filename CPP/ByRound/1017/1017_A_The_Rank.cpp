// Problem: CF 1017 A - The Rank
// https://codeforces.com/contest/1017/problem/A

/*
 * Problem: A. The Rank
 * Purpose: Determine the rank of Thomas Smith (id=1) among n students,
 *          based on total scores in four subjects (English, German, Math, History).
 *          Students are ranked by decreasing total score, and by increasing id if scores are equal.
 *
 * Algorithms/Techniques:
 *   - Single pass through data
 *   - Linear scan for ranking calculation
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long x(0), rank(1); // x stores Thomas's score, rank tracks current rank
  for (long p = 0; p < n; p++) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long s = a + b + c + d; // compute total score
    if (p == 0) {
      x = s; // Thomas is first student, store his score
    } else if (s > x) {
      ++rank; // if current student has higher score, increment rank
    }
  }
  printf("%ld\n", rank);
  return 0;
}


// https://github.com/VaHiX/codeForces/