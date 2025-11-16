// Problem: CF 1294 A - Collecting Coins
// https://codeforces.com/contest/1294/problem/A

/*
Problem: A. Collecting Coins
Purpose: Determine if it's possible to distribute n coins among three sisters such that all have equal number of coins.
Algorithm:
    - Find the maximum number of coins any sister currently has.
    - Calculate how many coins are needed to make all sisters have the same amount (difference from max).
    - Check two conditions:
      1. Total coins needed (diff) must be <= n.
      2. Remaining coins (n - diff) must be divisible by 3 to distribute equally among the three.
Time Complexity: O(1)
Space Complexity: O(1)

Input Format:
    First line contains t (number of test cases).
    Each test case has four integers a, b, c, n representing coins of Alice, Barbara, Cerene and total coins Polycarp has.
Output Format:
    For each test case print "YES" if distribution is possible, else "NO".
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, n;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &n);
    long mx = (a > b) ? a : b;           // Find maximum coins among the three sisters
    mx = (mx > c) ? mx : c;              // Update max with third value
    long diff = (mx - a) + (mx - b) + (mx - c);  // Calculate total coins needed to make all equal
    bool possible = (n >= diff) && ((n - diff) % 3 == 0);  // Check if n is sufficient and remaining divisible by 3
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/