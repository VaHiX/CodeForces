// Problem: CF 1699 A - The Third Three Number Problem
// https://codeforces.com/contest/1699/problem/A

/*
 * Problem: Find three integers a, b, c such that (a XOR b) + (b XOR c) + (a XOR c) = n
 *
 * Algorithm:
 * - Observing the XOR properties and the structure of the equation, we can derive that:
 *   If n is odd, it's impossible to express it as sum of three XOR results because XOR of
 *   two numbers is always even (each bit contributes 0 or 1 in XOR, so sum of three even numbers is even).
 *   If n is even, we can use simple construction:
 *     a = 0, b = 0, c = n / 2
 *     Then:
 *       (0 XOR 0) + (0 XOR (n/2)) + (0 XOR (n/2)) = 0 + (n/2) + (n/2) = n
 *
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) {  // If n is odd, no solution exists
      puts("-1");
    } else {
      printf("0 0 %ld\n", n / 2);  // Construct solution a=0, b=0, c=n/2
    }
  }
}


// https://github.com/VaHiX/CodeForces/