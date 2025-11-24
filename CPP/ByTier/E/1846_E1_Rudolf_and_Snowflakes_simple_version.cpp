// Problem: CF 1846 E1 - Rudolf and Snowflakes (simple version)
// https://codeforces.com/contest/1846/problem/E1

/*
 * Code purpose:
 * This program determines whether a given number of vertices n can form a valid snowflake
 * according to the defined rules. A snowflake is constructed starting with one vertex,
 * then adding k new vertices connected to the initial vertex, and continuing recursively
 * such that each leaf vertex adds k new vertices. The total number of vertices in such
 * a snowflake is of the form 1 + k + k^2 + ... + k^m for some integer m >= 1.
 *
 * Algorithm:
 * - Precompute all possible valid numbers of vertices (n) up to 1e6 by generating
 *   geometric series 1 + k + k^2 + ... + k^m for various values of k and m.
 * - Store these computed values in a set for fast lookup.
 * - For each query, check if the number exists in the set.
 *
 * Time complexity: O(k * log(N)) where k is around 1000 and N = 1e6
 * Space complexity: O(N) for storing the valid vertex counts in a set
 */

#include <cstdio>
#include <set>
int main() {
  const long N = 1e6 + 7;
  std::set<long> s;
  for (long k = 2; k < 1017; k++) {
    long cur = 1 + k;        // Start with 1 + k vertices (initial + k new)
    long nxt = k * k;        // Next term in series: k^2
    while (cur + nxt < N) {  // While adding next term doesn't exceed N
      cur += nxt;            // Add next term to current total
      s.insert(cur);         // Insert valid number of vertices into set
      nxt *= k;              // Move to next power of k
    }
  }
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(s.count(n) ? "YES" : "NO");  // Output YES/NO based on presence in set
  }
}


// https://github.com/VaHiX/CodeForces/