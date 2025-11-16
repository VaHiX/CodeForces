// Problem: CF 1981 A - Turtle and Piggy Are Playing a Game
// https://codeforces.com/contest/1981/problem/A

using System;
namespace C {
internal class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int j = 0; j < t; j++) {
      // Parse the input line to get r (upper bound) and ignore l (lower bound)
      int r = int.Parse(Console.ReadLine().Split(' ')[1]), s = 0;
      // While r is not 1, keep dividing by 2 and incrementing score
      while (r != 1) {
        r /= 2; // Divide r by 2 (equivalent to choosing p=2 each time)
        s++;    // Increment score for each division
      }
      Console.WriteLine(s); // Output the maximum score
    }
  }
}
}
/*
Algorithm: The problem is about finding the maximum number of operations to reduce a number to 1,
where each operation divides the number by the smallest prime factor (at each step, we choose p=2 to maximize score).
This reduces the problem to counting how many times we can divide r by 2 until it becomes 1.
This is essentially the number of bits in the binary representation minus 1, or log base 2 of r.

Time Complexity: O(log r) per test case, since we perform at most log(r) divisions.
Space Complexity: O(1), as we only use a constant amount of extra space.
*/

// https://github.com/VaHiX/CodeForces/