// Problem: CF 2003 B - Turtle and Piggy Are Playing a Game 2
// https://codeforces.com/contest/2003/problem/B

/*
 * Problem: B. Turtle and Piggy Are Playing a Game 2
 * 
 * Purpose: This code solves a game theory problem where two players (Turtle and Piggy)
 *          play optimally on a sequence of integers, taking turns to either maximize
 *          or minimize the value of the first element by applying max or min operations
 *          on adjacent elements and removing one of them.
 *          
 * Algorithm: The key insight is that since both players play optimally:
 *            - Turtle (maximizer) will always choose an index that maximizes a[0] at each step,
 *            - Piggy (minimizer) will always choose an index that minimizes a[0] at each step.
 *            However, after some analysis and simulation of the game process,
 *            it turns out that optimal play results in the median of the array.
 *            
 * Time Complexity: O(n log n) per test case due to sorting
 * Space Complexity: O(n) for storing the input array
 */

using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    
    while (T-- > 0) { // Process each test case
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of sequence
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the sequence
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      Array.Sort(a); // Sort the array to find the median efficiently
      Console.WriteLine(a[n / 2]); // Output the median which is the result
    }
  }
}


// https://github.com/VaHiX/codeForces/