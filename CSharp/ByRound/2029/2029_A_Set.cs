// Problem: CF 2029 A - Set
// https://codeforces.com/contest/2029/problem/A

/*
 * Problem: Maximum number of operations on a set of integers
 * 
 * Approach:
 * - We are given a range [l, r] and a value k.
 * - Each operation involves choosing an element x from the set such that there are at least k multiples of x in the set.
 * - After choosing x, we remove x from the set.
 * 
 * Key Insight:
 * - The optimal strategy is to always pick elements with the smallest value.
 * - Once we process a number x, we want to remove all multiples of x from the range.
 * - This can be modeled as a greedy selection where we process numbers in ascending order.
 * - However, a more efficient approach is to realize that we can count how many numbers in the range have at least k multiples.
 * 
 * Observation:
 * - If we consider multiples of a number `x`, they are x, 2x, 3x, ..., up to r.
 * - The count of multiples of x in range [l, r] is floor(r/x) - floor((l-1)/x).
 * - But instead of checking each x, we notice:
 *   - For a fixed k, we can count the number of valid x's such that there are at least k multiples.
 *   - This leads to a simpler formula: 
 *     - Count of numbers x in [l, r] where x has at least k multiples inside [l, r]
 *     - We can iterate x from l to r, but that's inefficient.
 *   - Better approach:
 *     - Iterate x from 1 to r, but only consider x where x*k <= r, since x*k is the smallest multiple that could exist.
 *     - But that isn't directly helpful either.
 *   - Efficient Solution:
 *     - The key idea is to count how large a subset of numbers we can "consume" greedily by picking them.
 *     - Actually, the solution follows from observing that this is essentially counting valid elements:
 *       - We iterate through numbers and see how many can be used as x in operation.
 *     - However, given constraints (up to 1e9), even a loop from l to r is impossible.
 *     - The optimal way is the following:
 *       - Consider all multiples of each number in the set, but do it in reverse.
 *       - Or rather, directly compute how many times we can perform an operation.
 * 
 * Formula Insight:
 * - The given code uses a very clever trick: 
 *   - The answer is: max(0, r/k - l + 1)  
 *   - This formula works because if we greedily take the largest elements first (larger x gives us more multiples),
 *     the number of operations equals the count of numbers whose value allows for at least k multiples in [l,r].
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
public class Set {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int l = int.Parse(parts[0]);   // Left boundary of the range
      int r = int.Parse(parts[1]);   // Right boundary of the range
      int k = int.Parse(parts[2]);   // Minimum required multiples
      int ans = Math.Max(0, r / k - l + 1);  // Compute maximum operations using formula
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/