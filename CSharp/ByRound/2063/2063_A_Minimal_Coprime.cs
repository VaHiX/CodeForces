// Problem: CF 2063 A - Minimal Coprime
// https://codeforces.com/contest/2063/problem/A

/*
 * Problem: Count the number of minimal coprime segments in [l, r]
 * Algorithm: Observing that a segment [l,r] is minimal coprime if and only if gcd(l, r) == 1,
 *            and no proper subsegment [l', r'] with l < l' < r' < r is coprime.
 *            The key insight is to use Euler's totient function or direct counting.
 *            However, by mathematical observation, the answer is simply φ(r) - φ(l-1),
 *            where φ(n) is Euler's totient function.
 *            
 *            But since we are given a simplified version with specific constraints,
 *            and from problem analysis:
 *            - For range [l,r], if l == 1, then result = 1 (only [1,1])
 *            - Otherwise: result = r - l
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int i = 0; i < t; i++) {
      string[] input = Console.ReadLine().Split(); // Read the segment [l, r]
      int a = int.Parse(input[0]); // Left boundary
      int b = int.Parse(input[1]); // Right boundary
      int result = (a == 1 && b == 1) ? 1 : b - a; // If both are 1, return 1. Else compute difference.
      Console.WriteLine(result); // Output the computed value
    }
  }
}


// https://github.com/VaHiX/codeForces/