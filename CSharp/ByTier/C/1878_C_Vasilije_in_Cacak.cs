// Problem: CF 1878 C - Vasilije in Cacak
// https://codeforces.com/contest/1878/problem/C

using System;
using System.Text;
public class VasilijeInCacak {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      long x = long.Parse(parts[2]);
      // Calculate minimum possible sum: 1 + 2 + ... + k
      long sMin = ((long)k * (k + 1)) / 2;
      // Calculate maximum possible sum: (n-k+1) + (n-k+2) + ... + n
      long sMax = ((long)k * (2 * n - k + 1)) / 2;
      // Check if x is within the possible range
      bool ansi = (x >= sMin && x <= sMax);
      ans.Append(ansi ? "YES" : "NO");
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}
/*
Purpose: Determine if k distinct integers from 1 to n can sum up to x.
Algorithm: 
- Use arithmetic progression formulas to compute the minimum and maximum possible sums for k distinct integers in range [1,n].
- Minimum sum is 1 + 2 + ... + k.
- Maximum sum is (n-k+1) + (n-k+2) + ... + n.
- If x lies within this range, output "YES", otherwise "NO".

Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1), only using a constant amount of extra space.
*/

// https://github.com/VaHiX/CodeForces/