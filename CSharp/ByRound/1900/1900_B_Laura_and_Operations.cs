// Problem: CF 1900 B - Laura and Operations
// https://codeforces.com/contest/1900/problem/B

/*
 * Problem: Laura and Operations
 * 
 * Algorithm/Approach:
 * - For each digit type (1, 2, 3), we determine if it's possible to reduce the board to only that digit.
 * - The key insight is that in each operation, we remove two different digits and add one different digit.
 *   This means the total count of digits decreases by 1 with each operation.
 * - The operation preserves the parity (even/odd nature) of the difference between the counts of any two digit types.
 * - So for a specific digit to be the last one remaining, it must be possible to reduce the other two digits to zero.
 *   This reduces to checking whether the difference between the counts of the other two types is even.
 * 
 * Time Complexity: O(t), where t is the number of test cases; each test case is processed in constant time.
 * Space Complexity: O(1) excluding the output string builder, which is linear in the number of outputs.
 */

using System;
using System.Text;
public class LauraAndOperations {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    int t = int.Parse(Console.ReadLine());
    for (int i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      byte a = byte.Parse(parts[0]);
      byte b = byte.Parse(parts[1]);
      byte c = byte.Parse(parts[2]);
      bool p1 = CheckDigit(a, b, c);  // Check if we can end with only digit 1
      bool p2 = CheckDigit(b, a, c);  // Check if we can end with only digit 2
      bool p3 = CheckDigit(c, a, b);  // Check if we can end with only digit 3
      ans.AppendFormat("{0} ", p1 ? 1 : 0);
      ans.AppendFormat("{0} ", p2 ? 1 : 0);
      ans.Append(p3 ? 1 : 0);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
  public static bool CheckDigit(byte x, byte n1, byte n2) {
    // Calculate absolute difference between counts of the other two types
    byte d = Convert.ToByte(n1 >= n2 ? n1 - n2 : n2 - n1);
    // If difference is even, then we can potentially eliminate one digit completely
    bool res = (d % 2 == 0);
    return res;
  }
}


// https://github.com/VaHiX/CodeForces/