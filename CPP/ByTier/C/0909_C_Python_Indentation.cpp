// Problem: CF 909 C - Python Indentation
// https://codeforces.com/contest/909/problem/C

/*
 * Problem: Python Indentation
 * 
 * Task: Given a sequence of statements ('f' for 'for' and 's' for 'simple'),
 * determine how many valid ways the statements can be indented to form
 * a syntactically correct Python program.
 *
 * Approach:
 * - Use dynamic programming with a vector `f` where f[i] represents the number
 *   of ways to indent the first i statements such that the i-th statement
 *   is at indentation level i.
 * - When encountering an 'f' (for loop), we extend the vector with a new zero,
 *   representing a new indentation level.
 * - When encountering an 's' (simple statement), we propagate the count of
 *   valid arrangements from previous levels to the current level, effectively
 *   summing up the valid ways to place this statement in a new scope.
 *
 * Time Complexity: O(N^2) due to nested loops over the size of f.
 * Space Complexity: O(N) for storing the vector f.
 */

#include <cstdio>
#include <vector>
int main() {
  const long MOD = 1000000007;
  long n;
  scanf("%ld\n", &n);
  std::vector<long> f;
  f.push_back(1);  // Base case: one way to start with no indentation
  for (long p = 0; p < n; p++) {
    char ch;
    scanf("%c\n", &ch);
    if (ch == 'f') {
      f.push_back(0);  // New indentation level for the 'for' statement
    } else {
      // For simple statement 's', accumulate the number of valid ways
      // from previous indentation levels to current one
      for (long q = 1; q < f.size(); q++) {
        f[q] += f[q - 1];
        f[q] %= MOD;
      }
    }
  }
  printf("%ld\n", f.back());
  return 0;
}


// https://github.com/VaHiX/CodeForces/