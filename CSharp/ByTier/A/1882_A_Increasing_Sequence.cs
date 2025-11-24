// Problem: CF 1882 A - Increasing Sequence
// https://codeforces.com/contest/1882/problem/A

/*
 * Problem: Increasing Sequence
 * Algorithm/Techniques: Greedy Algorithm
 * 
 * Time Complexity: O(n) per test case, where n is the length of the input sequence.
 * Space Complexity: O(1) excluding the input and output storage.
 * 
 * Approach:
 * - For each element in the sequence, we greedily assign the smallest possible value 
 *   to the corresponding element in the new sequence such that:
 *   1. It's a positive integer.
 *   2. It's different from the original element.
 *   3. It maintains the strictly increasing order.
 * 
 * We maintain a variable 'ansi' which represents the smallest valid value we can assign 
 * to the current position in the new sequence. If the current element in the input 
 * sequence equals 'ansi', we increment 'ansi' to ensure it's greater than the current
 * element and still maintains the increasing property.
 */

using System;
using System.Text;
public class IncreasingSequence {
  public static void Main() {
    StringBuilder ans = new StringBuilder();
    byte t = byte.Parse(Console.ReadLine());
    for (byte i = 0; i < t; i++) {
      byte n = byte.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      byte ansi = 0; // This will hold the minimum value of the last element in b
      for (byte j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]);
        ansi++; // Start by assuming the next number in sequence
        if (aj == ansi) // If this number is forbidden (same as input), skip it
          ansi++; // Increment again to avoid the forbidden number
      }
      ans.Append(ansi);
      ans.AppendLine();
    }
    Console.Write(ans);
  }
}


// https://github.com/VaHiX/CodeForces/