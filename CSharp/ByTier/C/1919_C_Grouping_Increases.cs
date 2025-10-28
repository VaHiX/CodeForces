// Problem: CF 1919 C - Grouping Increases
// https://codeforces.com/contest/1919/problem/C

/*
 * Problem: C. Grouping Increases
 * 
 * Algorithm/Technique: Greedy approach with tracking of two smallest elements
 * 
 * Time Complexity: O(n) - Each element is processed once.
 * Space Complexity: O(n) - Storing the input array of size n.
 * 
 * The problem asks to split an array into two subsequences such that the sum of 
 * penalties (number of increasing transitions) in both subsequences is minimized.
 * 
 * Key idea:
 * - A sequence with no increasing transitions has penalty 0.
 * - We can reduce the penalty by grouping elements in a way that minimizes
 *   the number of increasing transitions.
 * - The greedy strategy is to track the two smallest values seen so far.
 *   If a new element is greater than both, we must start a new group.
 *   This effectively models the "splitting" of sequences.
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
      long bmps = long.Parse(Console.ReadLine());
      while (bmps-- > 0) {
        long n = long.Parse(Console.ReadLine());
        string[] inputArray = Console.ReadLine().Split();
        long[] v = new long[n];
        for (long i = 0; i < n; i++) {
          v[i] = long.Parse(inputArray[i]);
        }
        long a = long.MaxValue, b = long.MaxValue, soul = 0;
        foreach (long i in v) {
          // Swap a and b if a > b to ensure a <= b
          if (a > b) {
            long temp = a;
            a = b;
            b = temp;
          }
          // If current element is <= a, update a
          if (i <= a) {
            a = i;
          }
          // If current element is <= b but > a, update b
          else if (i <= b) {
            b = i;
          }
          // If current element is greater than both a and b, 
          // it must start a new group, increment count
          else {
            a = i;
            soul++;
          }
        }
        Console.WriteLine($"{soul}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
}


// https://github.com/VaHiX/CodeForces/