// Problem: CF 988 A - Diverse Team
// https://codeforces.com/contest/988/problem/A

/*
 * Problem: A. Diverse Team
 * 
 * Purpose: 
 *   To form a team of k students such that all students in the team have distinct ratings.
 *   If possible, output "YES" and the indices of the students; otherwise output "NO".
 * 
 * Algorithm:
 *   - Use a map to store unique ratings and their first occurring indices.
 *   - Iterate through the students and add each student's rating to the map if it's not already there.
 *   - Once we have k unique ratings, we can form a valid team.
 *   - If we cannot collect k unique ratings, output "NO".
 * 
 * Time Complexity: O(n * log n)
 *   - We iterate n times, and in each iteration, map insertions take O(log n) time.
 * 
 * Space Complexity: O(n)
 *   - The map stores at most n elements in the worst case.
 */

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::map<long, long> m;  // Map to store unique ratings and their indices
  for (long p = 1; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    m[x] = p;  // Store the index of the first occurrence of rating x
    if (m.size() >= k) {  // If we have collected k unique ratings
      break;
    }
  }
  if (m.size() >= k) {
    puts("YES");
    for (std::map<long, long>::iterator it = m.begin(); it != m.end(); it++) {
      printf("%ld ", it->second);  // Print the indices of selected students
    }
    puts("");  // New line after printing indices
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/