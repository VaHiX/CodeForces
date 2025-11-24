// Problem: CF 866 A - Save the problem!
// https://codeforces.com/contest/866/problem/A

/*
 * Problem: Generate a test case for the coin change counting problem
 *          such that the number of ways to make change equals the given value A.
 *
 * Algorithm: This solution uses a clever mathematical approach.
 *            For any positive integer A, we can construct a test case:
 *              - Amount of change: 2*A - 1
 *              - Denominations: 1 and 2
 *            The number of ways to make change using only coins of denominations 1 and 2 
 *            is exactly 2*A - 1. This is because for any amount n, we can use k coins of 2
 *            and (n - 2*k) coins of 1, where k can range from 0 to floor(n/2).
 *            So the number of solutions is floor(n/2) + 1 = (n+1)/2 when n is odd.
 *            In our case n = 2*A - 1, so number of ways = (2*A - 1 + 1)/2 = A.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <iostream>
int main() {
  int a;
  std::cin >> a;
  std::cout << 2 * a - 1 << " 2\n1 2";  // Output the amount and denominations
  return 0;
}


// https://github.com/VaHiX/CodeForces/