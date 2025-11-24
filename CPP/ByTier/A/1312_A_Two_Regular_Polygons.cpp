// Problem: CF 1312 A - Two Regular Polygons
// https://codeforces.com/contest/1312/problem/A

/*
Problem: A. Two Regular Polygons
Purpose: Determine if a regular polygon with m vertices can be formed by selecting vertices from a regular polygon with n vertices, such that both polygons share the same center.

Algorithms/Techniques: 
- Mathematical check using modular arithmetic
- For a valid construction, m must divide n evenly (n % m == 0)

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

Input Format:
- First line: integer t (number of test cases)
- Next t lines: two integers n and m (vertices of initial and target polygons)

Output Format:
- For each test case, print "YES" if m divides n evenly, otherwise "NO"
*/

#include <cstdio>
int main() {
  long t;                     // Number of test cases
  scanf("%ld", &t);           // Read number of test cases
  while (t--) {               // Process each test case
    long m, n;                // Variables for number of vertices
    scanf("%ld %ld", &m, &n); // Read n and m
    puts((m % n == 0) ? "YES" : "NO"); // Check if m divides n evenly and print result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/