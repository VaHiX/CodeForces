// Problem: CF 1872 A - Two Vessels
// https://codeforces.com/contest/1872/problem/A

/*
 * Problem: Two Vessels
 * Algorithm: Greedy + Math
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Given two vessels with 'a' and 'b' grams of water respectively,
 * and a cup with capacity 'c', find the minimum number of moves
 * to make both vessels have equal amounts of water.
 *
 * Key idea:
 * - If a > b, swap them so that a <= b.
 * - The difference between a and b is (b - a).
 * - In each move, we can transfer at most 'c' grams.
 * - To minimize moves, we want to reduce the gap (b - a) using moves
 *   of size up to 'c'. This is essentially a ceiling division:
 *     ceil((b - a) / c)
 *
 * The formula used:
 *   diff = (b - a + 1) / 2
 *   ans = (diff + c - 1) / c
 *
 * However, since the question requires minimum moves to equalize masses,
 * it's simpler:
 *   diff = (b - a)
 *   min_moves = ceil(diff / c)
 *   But here we use an optimized version.
 *
 * The code actually first ensures a <= b, then computes how many times
 * 'c' fits into half of the difference to determine minimum moves.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    if (a > b) {
      long x = a;
      a = b;
      b = x;
    }
    long diff = (b - a + 1) / 2;      // Half the difference rounded up
    long ans = (diff + c - 1) / c;    // Ceiling division to get min moves
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/