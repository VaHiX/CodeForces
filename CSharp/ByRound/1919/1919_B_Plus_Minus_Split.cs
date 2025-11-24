// Problem: CF 1919 B - Plus-Minus Split
// https://codeforces.com/contest/1919/problem/B

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
      int t = int.Parse(Console.ReadLine());
      for (int testCase = 0; testCase < t; testCase++) {
        int n = int.Parse(Console.ReadLine());
        string s = Console.ReadLine();
        long result = TestCase(n, s);
        Console.WriteLine($"{result}");
      }
      Console.Out.Flush();
    } catch (Exception ex) {
      Console.WriteLine($"An error occurred: {ex.Message}");
    }
  }
  static long TestCase(int n, string s) {
    long sum = 0;
    // Calculate the total sum of the array where '+' = 1 and '-' = -1
    foreach (char i in s) {
      sum += (i == '-' ? -1 : 1);
    }
    // The minimum penalty is the absolute value of the total sum
    // Because the optimal split strategy is to avoid creating subarrays with non-zero sums
    return Math.Abs(sum);
  }
}
/*
Algorithm/Technique: Greedy approach
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a constant amount of extra space

The problem reduces to finding the minimum penalty of splitting an array of 1s and -1s.
The key insight is that we can minimize the penalty by avoiding splits that create subarrays with non-zero sums.
The optimal strategy is to keep the entire array as one subarray if the total sum is 0,
or split it in a way that balances out the prefix sums to minimize the penalty.
However, through analysis, the minimum penalty is simply the absolute value of the total sum,
since each unit in the array contributes to the final imbalance.

This greedy approach works because we want to minimize the sum of |prefix_sum| * length for subarrays.
The minimal total penalty is the absolute value of the total sum of all elements,
as any split that introduces additional segments will only increase the penalty unless the subarrays themselves sum to 0.
*/


// https://github.com/VaHiX/CodeForces/