// Problem: CF 937 A - Olympiad
// https://codeforces.com/contest/937/problem/A

/*
 * Code Purpose:
 * This program determines the number of ways to award diplomas to participants in an olympiad,
 * based on specific rules regarding scores and awarding criteria.
 *
 * Algorithm:
 * - Read all participant scores.
 * - Ignore any participant with a score of zero.
 * - Collect unique non-zero scores in a set to determine how many distinct score levels exist.
 * - The number of ways corresponds to the number of unique non-zero scores,
 *   because each unique score level defines a valid subset of award recipients.
 *
 * Time Complexity: O(n * log n) due to inserting elements into a set.
 * Space Complexity: O(n) for storing unique scores in the set.
 */

#include <cstdio>
#include <set>
int main() {
  long n;
  scanf("%ld", &n);
  std::set<long> s;  // Set to store unique non-zero scores
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a) {  // Only consider non-zero scores
      s.insert(a);
    }
  }
  printf("%ld\n", s.size());  // Output the count of unique non-zero scores
  return 0;
}


// https://github.com/VaHiX/CodeForces/