// Problem: CF 2028 A - Alice's Adventures in ''Chess''
// https://codeforces.com/contest/2028/problem/A

/*
 * Problem: Alice's Adventures in "Chess"
 * Algorithm/Technique: Simulation with cycle detection
 * 
 * Time Complexity: O(n * min(n, a+b)) where n is the length of the string s,
 *                  and a,b are the coordinates of the Red Queen.
 *                  In worst case, we simulate up to 200 steps or until we reach target.
 * Space Complexity: O(1) - only using a few variables for tracking position and loop control.
 * 
 * Description:
 * Alice starts at (0,0) and moves according to a fixed sequence of directions in string s.
 * The pattern repeats infinitely. We need to check if she ever reaches position (a,b).
 * 
 * Approach:
 * - For each test case, simulate Alice's movement step-by-step.
 * - Use a loop that runs at most 200 times (to avoid infinite loops due to cycles).
 * - Track her current x,y position and compare it with the target (a,b) at each step.
 * - If matching, output "YES". Otherwise, after trying enough steps, output "NO".
 */

using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' '); // Read n, a, b
      var n = int.Parse(line[0]);
      var a = int.Parse(line[1]);
      var b = int.Parse(line[2]);
      var s = Console.ReadLine().Trim(); // Read the movement string
      getAns(n, a, b, s);
    }
  }

  static void getAns(int n, int a, int b, string s) {
    var x = 0; // Current x-coordinate of Alice
    var y = 0; // Current y-coordinate of Alice
    var p = 0; // Step counter in the repeating pattern
    
    while (p < 200) { // Limit steps to prevent infinite loop, max possible steps is around 200 due to constraints
      var t = s[p % n]; // Get the direction from the repeating string
      
      if (t == 'N') // Move North (increase y)
        y++;
      else if (t == 'E') // Move East (increase x)
        x++;
      else if (t == 'W') // Move West (decrease x)
        x--;
      else // Move South (decrease y)
        y--;
      
      if (x == a && y == b) { // Check if current position matches Red Queen's position
        Console.WriteLine("YES");
        return;
      }
      p++;
    }
    Console.WriteLine("NO"); // If not reached in 200 steps, impossible to reach
  }
}


// https://github.com/VaHiX/codeForces/