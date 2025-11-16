// Problem: CF 1787 A - Exponential Equation
// https://codeforces.com/contest/1787/problem/A

#include <cstdio>
/**
 * Problem: Find integers x, y such that x^y * y + y^x * x = n
 * 
 * Algorithm:
 * - If n is odd, there's no solution because x^y * y + y^x * x is always even
 *   (since x^y * y and y^x * x are both even when x,y are both even or odd,
 *   and when one is even and one is odd, the sum is even)
 * - If n is even, let x = n/2 and y = 1
 *   Then: (n/2)^1 * 1 + 1^(n/2) * (n/2) = n/2 + n/2 = n
 * 
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) { // If n is odd, no solution exists
      puts("-1");
    } else {
      printf("%ld 1\n", n / 2); // Return n/2 and 1 as solution
    }
  }
}

// https://github.com/VaHiX/CodeForces/