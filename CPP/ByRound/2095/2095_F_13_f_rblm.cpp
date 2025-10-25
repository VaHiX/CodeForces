// Problem: CF 2095 F - ⅓ оf а Рrоblеm
// https://codeforces.com/contest/2095/problem/F

#include <bits/std_abs.h>
#include <cstdio>
int main() {
  long long a, b;                    // Declare two long long integers to store input values
  scanf("%lld %lld", &a, &b);        // Read two integers from standard input
  printf("%lld\n", 12 * a + 14 * a * b + std::abs(a - b) + (a - 3 * b) * b + 2);  // Calculate and print the result of the mathematical expression
}

/*
Problem: F. ⅓ оf а Рrоblеm
Time complexity: O(1) - constant time operations
Space complexity: O(1) - constant space usage
Algorithms/Techniques: Direct mathematical computation with absolute value function
*/

// https://github.com/VaHiX/codeForces/