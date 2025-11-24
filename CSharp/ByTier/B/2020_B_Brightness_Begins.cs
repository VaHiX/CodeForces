// Problem: CF 2020 B - Brightness Begins
// https://codeforces.com/contest/2020/problem/B

/* 
 * Problem: Brightness Begins
 * Purpose: Find the smallest number of light bulbs `n` such that after performing a series of flips based on divisibility,
 *          exactly `k` bulbs remain on.
 *
 * Algorithm:
 * - Each bulb `j` is flipped once for every divisor `i` of `j`.
 * - A bulb ends up on if it's flipped an odd number of times.
 * - The number of divisors of a number is odd if and only if it's a perfect square.
 * - Therefore, a bulb is on if its position is a perfect square.
 * - So the number of bulbs that are on for `n` bulbs is equal to the number of perfect squares <= n → ⌊√n⌋.
 *
 * We want to find the minimal `n` such that ⌊√n⌋ = k.
 * Since we're looking for exactly `k` bulbs on, we can binary search for the minimal `n`
 * such that the count of bulbs on is at least `k`.
 *
 * Time Complexity: O(T * log(max_n)) where T is number of test cases and max_n ≈ 10^18.
 * Space Complexity: O(1)
 */
using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var k = long.Parse(Console.ReadLine().Trim());
      getAns(k);
    }
  }
  static long calc(long t) {
    // Calculates how many perfect squares are <= t
    var w = (long)Sqrt(t);
    if (w * w > t)
      return t - (w - 1); // If w^2 > t, then there are w-1 perfect squares <= t
    else
      return t - w; // Otherwise, there are w perfect squares <= t
  }
  static void getAns(long k) {
    if (k == 1) {
      Console.WriteLine(2); // Special case handling
      return;
    }
    var ng = 1L;        // Lower bound for binary search
    var ok = long.MaxValue; // Upper bound for binary search
    while (ok - ng > 1) {
      var mid = ng + (ok - ng) / 2;
      if (calc(mid) >= k)
        ok = mid;   // Mid is a valid candidate, try smaller
      else
        ng = mid;   // Mid is too small, need larger value
    }
    Console.WriteLine(ok);
  }
}


// https://github.com/VaHiX/codeForces/