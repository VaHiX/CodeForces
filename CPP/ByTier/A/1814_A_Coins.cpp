// Problem: CF 1814 A - Coins
// https://codeforces.com/contest/1814/problem/A

/*
 * Problem: Coins
 * Algorithms/Techniques: Mathematical analysis
 * 
 * Given two coin denominations 2 and k, determine if it's possible to make amount n.
 * This is equivalent to finding non-negative integers x and y such that 2*x + k*y = n.
 * 
 * Key insight:
 * - If n is even, we can always use only coins of denomination 2 (x = n/2).
 * - If n is odd, then k must be odd for there to exist a solution with at least one coin of denomination k.
 *   Specifically, if (n - k) is even, then y = (n - k)/k gives us a valid x = 0.
 *   
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    long long n, k; // amount to make and coin denomination
    scanf("%lld %lld", &n, &k);
    bool res = (n % 2 == 0) || ((n - k) % 2 == 0); // check conditions for solvability
    puts(res ? "YES" : "NO"); // output result
  }
}


// https://github.com/VaHiX/codeForces/