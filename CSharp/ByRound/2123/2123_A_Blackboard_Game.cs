// Problem: CF 2123 A - Blackboard Game
// https://codeforces.com/contest/2123/problem/A

/*
 * Problem: Blackboard Game
 * Purpose: Determine the winner of a game between Alice and Bob on a blackboard with integers from 0 to n-1
 *          where players alternate choosing numbers according to a modulo constraint.
 *
 * Algorithms/Techniques:
 *   - Mathematical analysis based on modulo arithmetic (mod 4)
 *   - Game theory with optimal play assumptions
 *   - Observation-based logic to determine win/loss conditions
 *
 * Time Complexity: O(1) per test case - constant time operations
 * Space Complexity: O(1) - only using a fixed amount of variables regardless of input size
 */

using System;
class HelloWorld {
  static void Main() {
    int x = 0;               // Number of test cases
    int t = 0;               // Current test case value (n)
    int sum = 0;             // Temporary variable for accumulation (unused in final logic)
    x = int.Parse(Console.ReadLine()); // Read number of test cases
    
    for (int i = 0; i < x; i++) { // Process each test case
      sum = 0;                // Reset sum (not actively used after initial check)
      t = int.Parse(Console.ReadLine()); // Read current n value
      
      if (t % 2 != 0)         // If n is odd, Alice wins immediately (observation from problem analysis)
        Console.WriteLine("Alice");
      else {                  // If n is even, apply the more complex logic
        
        // The loop below calculates a cumulative sum but isn't used in final decision
        for (int j = 0; j < t; j++) {
          sum += j;
        }
        
        if (sum % 2 != 0) {   // This condition is never met for even n due to arithmetic properties
          Console.WriteLine("Alice");
        } else
          Console.WriteLine("Bob");
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/