// Problem: CF 1921 B - Arranging Cats
// https://codeforces.com/contest/1921/problem/B

/*
 * Problem: B. Arranging Cats
 * 
 * Purpose: This code computes the minimum number of operations required to transform an initial arrangement of cats in boxes into a desired arrangement.
 *          Each operation can be: placing a cat in an empty box, removing a cat from a box, or moving a cat from one box to another.
 * 
 * Algorithm:
 *   - For each position i:
 *     - If current state is '0' and target is '1': increment counter 'a'
 *     - If current state is '1' and target is '0': increment counter 'b'
 *   - The result is the maximum of 'a' and 'b'
 * 
 * Time Complexity: O(n) where n is the number of boxes.
 * Space Complexity: O(1) - only using a constant amount of extra space.
 */

using System;
class Program {
  static void Main() {
    try {
      Console.SetIn(new System.IO.StreamReader(Console.OpenStandardInput(),
                                               Console.InputEncoding, false,
                                               bufferSize: 1024));
      Console.SetOut(new System.IO.StreamWriter(Console.OpenStandardOutput(),
                                                Console.OutputEncoding,
                                                bufferSize: 1024));
      long t = long.Parse(Console.ReadLine());
      for (long testCase = 0; testCase < t; testCase++) {
        long n = long.Parse(Console.ReadLine());
        string s = Console.ReadLine();
        string target = Console.ReadLine();
        long result = solve(n, s, target);
        Console.WriteLine($"{result}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static long solve(long n, string s, string target) {
    long a = 0; // Count of boxes that need to be filled (0 -> 1)
    long b = 0; // Count of boxes that need to be emptied (1 -> 0)
    for (long i = 0; i < n; i++) {
      if (s[(int)i] == '0' && target[(int)i] != '0') {
        a++;
      }
      if (s[(int)i] == '1' && target[(int)i] == '0') {
        b++;
      }
    }
    return Math.Max(a, b); // Minimum operations needed is max of these two counts
  }
}


// https://github.com/VaHiX/CodeForces/