// Problem: CF 1692 A - Marathon
// https://codeforces.com/contest/1692/problem/A

/*
 * Problem: Marathon
 * Purpose: Determine how many participants have run a greater distance than Timur.
 * Algorithm: For each test case, compare Timur's distance 'a' with the distances of the other three participants 'b', 'c', and 'd'.
 *            Count how many of these are greater than 'a'.
 * Time Complexity: O(t), where t is the number of test cases. Each test case does a constant amount of work.
 * Space Complexity: O(1). Only a fixed number of variables are used regardless of input size.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);  // Read number of test cases
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);  // Read the four distances
    printf("%d\n", (b > a) + (c > a) + (d > a));  // Count how many are greater than Timur's distance 'a'
  }
}


// https://github.com/VaHiX/codeForces/