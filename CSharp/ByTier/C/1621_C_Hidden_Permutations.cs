// Problem: CF 1621 C - Hidden Permutations
// https://codeforces.com/contest/1621/problem/C

﻿/*
Algorithm: 
This problem involves deducing a hidden permutation p by querying a transformed permutation q. 
The key insight is that q is transformed via q'[i] = q[p[i]] in each step. 
We determine p by tracking how values move through the transformation and using the fact that we can 
trace the cycle of positions from a starting index.

Approach:
1. Initialize the answer array to store indices that map to their final positions in p.
2. Query q[1] initially to start the first sequence.
3. For each starting index, follow the transformation cycle:
   - Query q[index] to get the current value.
   - Record that the previous value maps to the current value in the answer array.
   - Continue until we return to the starting value, completing a cycle.
4. Find the next unassigned index and repeat the process for a new cycle.
5. Output the final permutation p.

Time Complexity: O(n)
Space Complexity: O(n)
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace SecretChanges1621C {
class Program {
  static void Main(string[] args) {
    int t = Int32.Parse(Console.ReadLine());
    for (int p = 0; p < t; p++) {
      int n = Int32.Parse(Console.ReadLine());
      int[] answer = new int[n + 1]; // Stores the mapping for permutation p
      Console.WriteLine("? 1");
      Console.Out.Flush();
      Console.ReadLine();
      int index = 1; // The next unassigned position in the answer
      int firstNum = 1; // The starting value for the current cycle
      int prevNum = 1; // Previous value in the current transformation path
      while (index <= n) {
        do {
          // Query the current position and record the transformation
          Console.WriteLine("? " + index);
          Console.Out.Flush();
          int currNum = Int32.Parse(Console.ReadLine());
          answer[prevNum] = currNum; // This says that prevNum maps to currNum in p
          prevNum = currNum; // For the next iteration, currNum becomes the previous value
        } while (prevNum != firstNum); // Continue until we return to the starting value
        // Find the next unassigned index to begin a new cycle
        while (index <= n && answer[index] != 0) {
          ++index;
        }
        if (index <= n) {
          Console.WriteLine("? " + index);
          Console.Out.Flush();
          prevNum = Int32.Parse(Console.ReadLine());
          firstNum = prevNum; // Set the new starting value
        }
      }
      // Output the constructed permutation
      Console.Write("! ");
      for (int i = 1; i <= n; i++) {
        Console.Write(answer[i]);
        if (i != n)
          Console.Write(" ");
      }
      Console.WriteLine();
      Console.Out.Flush();
    }
  }
}
}


// https://github.com/VaHiX/CodeForces/