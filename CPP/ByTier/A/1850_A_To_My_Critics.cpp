// Problem: CF 1850 A - To My Critics
// https://codeforces.com/contest/1850/problem/A

/*
Problem: A. To My Critics
Purpose: Determine if any two of the three given digits can sum to at least 10.
Algorithm: Check all three possible pairs (a+b, b+c, c+a) for sums >= 10.
Time Complexity: O(1) - constant time per test case as there are only a fixed number of operations.
Space Complexity: O(1) - only using a constant amount of extra space.

Input Format:
- First line contains t (number of test cases)
- Each test case contains three digits a, b, c (0 ≤ a,b,c ≤ 9)

Output Format:
- "YES" if any pair sums to at least 10, otherwise "NO"
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of test cases
  while (t--) { // Process each test case
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c); // Read three digits
    bool ans = (a + b >= 10) || (b + c >= 10) || (c + a >= 10); // Check all pairs
    puts(ans ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/