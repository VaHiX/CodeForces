// Problem: CF 2032 A - Circuit
// https://codeforces.com/contest/2032/problem/A

/*
 * Problem: Circuit
 * Purpose: Determine the minimum and maximum number of lights that can be turned on
 *          given the states of 2n switches, where each light is connected to exactly
 *          two switches and each switch is connected to exactly one light.
 *
 * Algorithm:
 * - Count total number of switches that are on (c1) and off (c0).
 * - For maximum lights on:
 *   - Each pair of switches connected to the same light contributes 1 to max,
 *     as we can arrange such that only one switch in each pair is on.
 *   - If c1 >= c0, we can arrange so all lights are on up to c0 (as every light
 *     must have at least one off switch if there are more switches than lights).
 *   - If c1 < c0, then all lights can be on up to the full number of lights n.
 * - For minimum lights on:
 *   - We try to assign all switches to minimize total lights on.
 *   - If c1 is odd, at least one light remains off.
 *   - If c1 is even, we might get zero lights on if pairs match perfectly.
 *
 * Time Complexity: O(n), where n is the number of lights. Parsing input and summation are linear.
 * Space Complexity: O(1), only using a few variables for computation.
 */

using System.Linq;
using static System.Math;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read number of lights
      string[] line = Console.ReadLine().Trim().Split(' '); // Read switch states
      var a = Array.ConvertAll(line, int.Parse); // Convert to integer array
      getAns(n, a); // Compute and output result
    }
  }
  
  static void getAns(int n, int[] a) {
    var c1 = a.Sum(); // Count how many switches are on
    var c0 = n + n - c1; // Total switches - on switches = off switches

    // Maximum number of lights that can be on:
    // In best case, we pair up switches optimally to maximize light states.
    var offmax = c1 / 2 + c0 / 2; // This represents maximum possible lights ON
    var minon = n - offmax;       // Minimum lights ON = Total lights - Maximum lights OFF
    
    // Maximum number of lights that can be on:
    // When switches are assigned optimally, at most min(c0, c1) lights can be turned ON
    var maxon = Min(c0, c1);
    
    Console.WriteLine("{0} {1}", minon, maxon); // Output the minimum and maximum number of lights on
  }
}


// https://github.com/VaHiX/codeForces/