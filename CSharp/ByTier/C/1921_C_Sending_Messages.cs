// Problem: CF 1921 C - Sending Messages
// https://codeforces.com/contest/1921/problem/C

/*
 * Problem: Sending Messages
 * 
 * Algorithm/Technique: Greedy Approach with Prefix Sum Optimization
 * 
 * Time Complexity: O(n) per test case, where n is the number of messages.
 *                  The total time complexity across all test cases is O(∑n) due to the constraint on sum of n.
 * 
 * Space Complexity: O(n) for storing the message times array.
 * 
 * Approach:
 * - For each message, decide whether to turn the phone off and on or just continue using it.
 * - At each step, calculate the cost of: (1) turning off and on the phone, or (2) continuing without turning off.
 * - Choose the option that costs less.
 * - Keep track of remaining battery charge.
 * - If at any point the battery becomes non-positive, output "NO".
 * - If all messages can be sent, output "YES".
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
        string[] input = Console.ReadLine().Split();
        long n = long.Parse(input[0]);
        long f = long.Parse(input[1]);
        long a = long.Parse(input[2]);
        long b = long.Parse(input[3]);
        long[] m = new long[n];
        string[] mInput = Console.ReadLine().Split();
        for (long i = 0; i < n; i++) {
          m[i] = long.Parse(mInput[i]);
        }
        long p = 0; // previous message time
        long c; // cost for current step
        for (long i = 0; i < n; i++) {
          // Calculate the minimum cost between turning off/on or continuing without turning off
          c = Math.Min(b, Math.Abs(m[i] - p) * a);
          f -= c;
          p = m[i]; // update the previous message time
        }
        if (f > 0) {
          Console.WriteLine("YES");
        } else {
          Console.WriteLine("NO");
        }
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/