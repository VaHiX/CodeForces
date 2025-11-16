// Problem: CF 1311 A - Add Odd or Subtract Even
// https://codeforces.com/contest/1311/problem/A

/*
 * Problem: A. Add Odd or Subtract Even
 * Purpose: Given two positive integers a and b, find the minimum number of moves to transform a into b.
 *          In each move, we can either add an odd number or subtract an even number.
 *
 * Algorithms/Techniques: 
 *   - Mathematical analysis based on parity (odd/even) of difference between a and b
 *   
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Explanation:
 *   If a == b, no moves needed.
 *   Otherwise, the minimum moves depend on the difference (b - a):
 *   - If b > a and difference is odd: 1 move (add odd number)
 *   - If b > a and difference is even: 2 moves (add odd number twice or subtract even then add odd)
 *   - If a > b and difference is even: 1 move (subtract even number)
 *   - If a > b and difference is odd: 2 moves (subtract even then add odd or vice versa)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (a == b) {
      puts("0");
    } else if ((b > a) && ((b - a) % 2 == 1)) {
      puts("1");
    } else if ((b > a) && ((b - a) % 2 == 0)) {
      puts("2");
    } else if ((a > b) && ((a - b) % 2 == 0)) {
      puts("1");
    } else if ((a > b) && ((a - b) % 2 == 1)) {
      puts("2");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/