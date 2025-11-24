// Problem: CF 1981 B - Turtle and an Infinite Sequence
// https://codeforces.com/contest/1981/problem/B

/*
 * Purpose: This code computes the value of a_n after m seconds in a sequence that evolves according to a specific bitwise OR rule.
 * Algorithm: The solution uses bit manipulation and observes that the evolution of the sequence stabilizes after certain steps based on the binary representation of n and the number of steps m.
 * 
 * Time Complexity: O(log n + log m), as we iterate through the bits of n and then expand ind until it exceeds the remaining steps.
 * Space Complexity: O(1), as we only use a constant number of variables regardless of input size.
 * 
 * Techniques:
 * - Bitwise operations and binary representation analysis
 * - Simulation of evolution pattern without full array simulation
 */

using System;
class Program {
  static void Main(string[] args) {
    int test = Convert.ToInt32(Console.ReadLine());
    while (test-- > 0) {
      Sol();
    }
  }
  static void Sol() {
    string[] input = Console.ReadLine().Split();
    long n = Convert.ToInt64(input[0]);
    long m = Convert.ToInt64(input[1]);
    long ind = 1, num = 0, ans = 0;
    while (n > 0) {
      if (n % 2 == 1) {
        // If the current bit is set, add the corresponding power of 2 to ans and num
        ans += ind;
        num += ind;
      } else {
        // If the current bit is not set, determine if it will be set after m steps
        long x = Math.Min(ind - num, num + 1);
        if (x <= m) {
          ans += ind;
        }
      }
      ind *= 2;
      n /= 2;
    }
    // After processing all bits of n, continue extending the answer if needed for remaining steps
    while (ind - num <= m) {
      ans += ind;
      ind *= 2;
    }
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/CodeForces/