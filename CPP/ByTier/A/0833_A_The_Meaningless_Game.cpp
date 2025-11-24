// Problem: CF 833 A - The Meaningless Game
// https://codeforces.com/contest/833/problem/A

/*
 * Problem: A. The Meaningless Game
 * 
 * Purpose: Determine if a given pair of scores (a, b) can be achieved through a sequence of rounds
 *          where each round multiplies the winner's score by k^2 and the loser's by k.
 * 
 * Algorithm:
 *   1. For each pair (a, b), compute the product a * b.
 *   2. Check if the cube root of a * b is an integer, call it x.
 *   3. If x is valid and both a and b are divisible by x, then the result is "Yes".
 * 
 * Key Idea:
 *   The final scores a and b are obtained by multiplying by factors k and k^2 in various rounds.
 *   The cube root of (a * b) gives the product of all k's used in the game.
 * 
 * Time Complexity: O(n * log B) where n is number of test cases and B = 1e6 + 10
 * Space Complexity: O(1)
 */

#include <stdint.h>
#include <cstdio>

const int64_t B = 1e6 + 10;
int64_t cubicRoot(int64_t x) {
  int64_t left(0), right(B);
  while (left <= right) {
    int64_t mid = (left + right) / 2;
    int64_t test = mid * mid * mid;
    if (test == x) {
      return mid;
    } else if (test < x) {
      left = mid + 1;
    } else if (test > x) {
      right = mid - 1;
    }
  }
  return 0;
}
int main() {
  long n;
  scanf("%ld", &n);
  while (n--) {
    int64_t a, b;
    scanf("%lld %lld", &a, &b);
    int64_t x = cubicRoot(a * b);
    puts(((x > 0) && (a % x == 0) && (b % x == 0)) ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/