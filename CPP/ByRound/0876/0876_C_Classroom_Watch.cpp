// Problem: CF 876 C - Classroom Watch
// https://codeforces.com/contest/876/problem/C

/*
 * Purpose: This program finds all positive integers x such that x plus the sum of its digits equals a given number n.
 *          For each valid x, it outputs the value. If no such x exists, it outputs 0.
 *
 * Algorithm:
 *   - Iterate through possible values of x from a calculated lower bound up to n.
 *   - For each x, compute the sum of its digits.
 *   - Check if x + digit_sum equals n.
 *   - If yes, add x to result list.
 *
 * Time Complexity: O((n - start) * log n), where 'start' is the beginning of search range.
 *                  In worst case, this is approximately O(n * log n), since for each x we compute digit sum in O(log x).
 *
 * Space Complexity: O(k), where k is the number of valid x values found (at most ~10^9 in the worst case, but typically much less).
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> v;
  // Lower bound for x is n - 81 because maximum digit sum for a number with 10 digits is 9*10 = 90,
  // but for n=10^9, the minimum x must be less than or equal to n - 81 for any solution to exist.
  long start(n <= 81 ? 1 : n - 81);
  for (long p = start; p <= n; p++) {
    long m(p), sd(0);
    // Compute sum of digits of p
    while (m > 0) {
      sd += m % 10;
      m /= 10;
    }
    // If x + digit_sum equals n, then x is a valid solution
    if (p + sd == n) {
      v.push_back(p);
    }
  }
  printf("%ld\n", v.size());
  for (long p = 0; p < v.size(); p++) {
    printf("%ld\n", v[p]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/