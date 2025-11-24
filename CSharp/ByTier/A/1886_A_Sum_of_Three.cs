// Problem: CF 1886 A - Sum of Three
// https://codeforces.com/contest/1886/problem/A

/*
 * Problem: Sum of Three
 * 
 * Purpose: To find three distinct positive integers x, y, z such that:
 *   - x + y + z = n
 *   - None of x, y, z are divisible by 3
 * 
 * Algorithm:
 * - Determine remainder r = n % 3
 * - Based on r, check if a valid triplet exists using conditions:
 *   - If r == 0: need at least 12 to allow three distinct numbers not divisible by 3
 *   - If r == 1: need at least 7
 *   - If r == 2: need at least 8
 * - If valid, construct a simple solution with:
 *   - x = 1 (not divisible by 3)
 *   - y = 2 if r > 0 else 4 (ensures y is not divisible by 3)
 *   - z = n - x - y (ensures the sum equals n)
 * 
 * Time Complexity: O(t), where t is the number of test cases (each operation is constant time)
 * Space Complexity: O(1) for computation, O(n) for output string builder used for storing results
 */

using System;
using System.Text;
public class SumOfThree {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      byte r = Convert.ToByte(n % 3);
      bool existSolution =
          ((r == 0 && n >= 12) || (r == 1 && n >= 7) || (r == 2 && n >= 8));
      if (existSolution) {
        ans.Append("YES");
        ans.AppendLine();
        byte x = 1;
        byte y = Convert.ToByte(r > 0 ? 2 : 4); // Choose y such that it's not divisible by 3
        int z = (r > 0 ? n - 3 : n - 5); // Compute z to make sure sum equals n
        ans.AppendFormat("{0} {1} {2}", x, y, z);
      } else
        ans.Append("NO");
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/