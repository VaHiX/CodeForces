// Problem: CF 1987 A - Upload More RAM
// https://codeforces.com/contest/1987/problem/A

/*
 * Problem: Upload More RAM
 * 
 * Algorithm/Technique: Mathematical Observation
 * 
 * Time Complexity: O(t), where t is the number of test cases. Each test case is processed in constant time.
 * Space Complexity: O(1), only using a constant amount of extra space regardless of input size.
 * 
 * Approach:
 * - We are given n GBs to upload and a constraint that in any k consecutive seconds, we can upload at most 1 GB.
 * - To minimize the number of seconds, we should try to pack as much as possible into the allowed k-second windows.
 * - In each k-second window, we can upload at most 1 GB. If we have n GBs to upload, we can divide them into groups of k seconds,
 *   each group contributing at most 1 GB.
 * - Therefore, we need at least n * k seconds to satisfy the constraint, but we can optimize by noting that
 *   the last k-1 seconds of each group (except the final one) can be used to accumulate data in a way that doesn't count towards a new k-window.
 * - A more direct optimal strategy:
 *   - Each full k-second window contributes 1 GB, but we can do better by using a sliding window approach.
 * - However, a simpler and correct approach:
 *   - The minimum time is given by: n * k - (k - 1)
 *   - This works because we can use k-1 seconds of the first window to accumulate before starting a new one,
 *     and then continue in an optimal way.
 * 
 * Example:
 *   n = 5, k = 1
 *   ans = 5 * 1 - (1 - 1) = 5
 *   n = 2, k = 2
 *   ans = 2 * 2 - (2 - 1) = 3
 *   n = 2, k = 3
 *   ans = 2 * 3 - (3 - 1) = 4
 * 
 */

using System;
using System.IO;
using System.Text;
public class Program {
  public static void Main() {
    StreamReader reader = new StreamReader(Console.OpenStandardInput());
    StringBuilder output = new StringBuilder();
    long t = long.Parse(reader.ReadLine());
    while (t-- > 0) {
      string[] input = reader.ReadLine().Split();
      long n = long.Parse(input[0]);  // Number of GBs to upload
      long k = long.Parse(input[1]);  // Size of the time window
      long ans = n * k;               // Base case: n windows of k seconds each
      ans -= (k - 1);                 // Adjust for overlapping window optimization
      output.AppendLine(ans.ToString());
    }
    Console.Write(output.ToString());
  }
}


// https://github.com/VaHiX/CodeForces/