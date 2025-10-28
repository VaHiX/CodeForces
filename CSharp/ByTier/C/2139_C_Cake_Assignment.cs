// Problem: CF 2139 C - Cake Assignment
// https://codeforces.com/contest/2139/problem/C

/*
C. Cake Assignment
Algorithms/Techniques: Greedy algorithm with bit manipulation and reverse simulation.

Time Complexity: O(log(2^{k+1})) = O(k), since at each step we halve one of the values.
Space Complexity: O(log(2^{k+1})) = O(k), for storing the sequence of operations.

The problem involves redistributing cakes between two people such that one ends up with exactly x cakes.
We simulate the reverse process - starting from the target (x, 2^(k+1)-x) and working back to initial state (2^k, 2^k).
At each step, we determine whether to add or subtract halved amounts based on which person has more cakes,
and record the operation type in reverse order. Finally, the list is reversed to obtain the actual sequence.
*/

using System;
using System.Collections.Generic;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      var parts = Console.ReadLine().Split();
      long k = long.Parse(parts[0]);
      ulong x = ulong.Parse(parts[1]); // target cakes for Chocola
      ulong total = 1UL << (int)(k + 1); // total number of cakes = 2^(k+1)
      ulong a = x, b = total - x; // a: Chocola's current cakes, b: Vanilla's current cakes
      var steps = new List<int>(); // stores operations in reverse order

      // Simulate the reverse process until both have equal cakes
      while (a != b) {
        if (a < b) {
          // Chocola has fewer cakes; she receives half of Vanilla's cakes
          steps.Add(1); // operation 1: Chocola gets half of Vanilla's cakes
          b -= a;
          a += a;
        } else {
          // Vanilla has fewer cakes; she receives half of Chocola's cakes
          steps.Add(2); // operation 2: Vanilla gets half of Chocola's cakes
          a -= b;
          b += b;
        }
      }

      // Reverse the list to get the correct order of operations
      steps.Reverse();
      Console.WriteLine(steps.Count);
      Console.WriteLine(string.Join(" ", steps));
    }
  }
}


// https://github.com/VaHiX/codeForces/