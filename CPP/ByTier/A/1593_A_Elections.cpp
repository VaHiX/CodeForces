// Problem: CF 1593 A - Elections
// https://codeforces.com/contest/1593/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long mx = (a > b) ? a : b; // Find maximum of a and b
    mx = (mx > c) ? mx : c; // Update mx to be maximum of a, b, and c
    bool tie = (((a == mx) + (b == mx) + (c == mx)) > 1); // Check if there's a tie for the maximum
    long u = (a == mx) ? tie : (mx + 1 - a); // Calculate votes needed for candidate a
    long v = (b == mx) ? tie : (mx + 1 - b); // Calculate votes needed for candidate b
    long w = (c == mx) ? tie : (mx + 1 - c); // Calculate votes needed for candidate c
    printf("%ld %ld %ld\n", u, v, w);
  }
}
/*
Problem: Elections
Time Complexity: O(1) per test case
Space Complexity: O(1)

The code solves the problem of determining how many additional votes each candidate needs to win.
For each test case:
- It finds the maximum number of votes among the three candidates.
- If there's a tie for the maximum, then each tied candidate needs 1 vote to win (tie = true).
- Otherwise, each candidate needs enough votes to surpass the maximum by at least 1.
This algorithm works in constant time as it only performs a fixed number of operations regardless of input size.
*/

// https://github.com/VaHiX/codeForces/