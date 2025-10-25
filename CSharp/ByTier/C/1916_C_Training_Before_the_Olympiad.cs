// Problem: CF 1916 C - Training Before the Olympiad
// https://codeforces.com/contest/1916/problem/C

/*
 * Problem: C. Training Before the Olympiad
 * 
 * Algorithm/Technique: 
 *   - Greedy approach with observation on how the operation affects parity and value
 *   - Key insight: The operation ⌊(a_i + a_j) / 2⌋ * 2 essentially rounds down the average and multiplies by 2
 *   - Observing that odd numbers affect the outcome differently than even numbers
 *   - For each prefix, compute the result by tracking counts of even and odd numbers
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the input array
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
        Solve();
        Console.WriteLine();
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static void Solve() {
    long n = long.Parse(Console.ReadLine());
    long[] arr = new long[n];
    string[] arrInput = Console.ReadLine().Split();
    for (long i = 0; i < n; i++) {
      arr[i] = long.Parse(arrInput[i]);
    }
    long evecnt = 0; // Count of even numbers
    long oddcnt = 0; // Count of odd numbers
    long sum = 0;    // Running sum of all elements
    for (long i = 0; i < n; i++) {
      sum += arr[i];
      if (arr[i] % 2 == 0) {
        evecnt++;
      } else {
        oddcnt++;
      }
      if (i == 0) {
        Console.Write($"{sum} ");
        continue;
      }
      // The key logic for the optimal game result:
      // Based on the number of odd elements, determine the final value
      // This is derived from game theory and optimal play analysis.
      long curr_ans = sum - (oddcnt / 3);
      if (oddcnt % 3 == 1) {
        curr_ans--; // Adjust for the special case when there's one extra odd number
      }
      Console.Write($"{curr_ans} ");
    }
  }
}


// https://github.com/VaHiX/CodeForces/