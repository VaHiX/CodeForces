// Problem: CF 1761 A - Two Permutations
// https://codeforces.com/contest/1761/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    bool res = (a == n && b == n) || (a + b + 1 < n); // Check if it's possible to construct two permutations with given prefix and suffix lengths
    puts(res ? "Yes" : "No");
  }
}
/*
Problem: A. Two Permutations
Purpose: Determine if there exist two permutations of length n such that their longest common prefix is a and longest common suffix is b.
Algorithm: Mathematical check based on constraints of prefix and suffix overlap.
Time Complexity: O(1) - constant time per test case.
Space Complexity: O(1) - only using a few variables.
*/

// https://github.com/VaHiX/codeForces/